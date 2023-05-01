# Get the Official Jenkins Docker Image
FROM jenkins/jenkins:lts-jdk11

ENV JAVA_OPTS -Djenkins.install.runSetupWizard=false \
# allow local checkout in git scm to be able to see local repository
  -Dhudson.plugins.git.GitSCM.ALLOW_LOCAL_CHECKOUT=true \
# allows notifyCommit with unauthenticated requests
  -Dhudson.plugins.git.GitStatus.NOTIFY_COMMIT_ACCESS_CONTROL=disabled-for-polling

USER root

ARG CMAKE_VERSION=3.26.3
ARG CMAKELINK=https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/
ARG CMAKEFILEPREFIX=cmake-${CMAKE_VERSION}
ARG CMAKELINUXFILE=${CMAKEFILEPREFIX}-linux-x86_64.sh
ARG CMAKEWINDOWSFILE=${CMAKEFILEPREFIX}-windows-x86_64.msi

# enable i386 architecture to be able to install wine32
RUN dpkg --add-architecture i386 \
# install packages (including recommended) and dependencies
    && apt-get update && apt-get -y install \
    build-essential \
    wget \
    gcc \
    g++ \
    mingw-w64 \
    python3 \
    wine \
    xvfb \
    # remove cache packages
    && rm -fr /var/lib/apt/lists/* \
    # install specific cmake version
    && wget ${CMAKELINK}${CMAKELINUXFILE} -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /opt/cmake-${CMAKE_VERSION} \
      && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-${CMAKE_VERSION} \
      && rm /tmp/cmake-install.sh \
      && ln -s /opt/cmake-${CMAKE_VERSION}/bin/* /usr/local/bin \
    # install winetricks through here because it's not available as a package...
    && curl -o winetricks https://raw.githubusercontent.com/Winetricks/winetricks/master/src/winetricks \
    # make it executable
    && chmod +x winetricks \
    # move it to binaries
    && mv winetricks /usr/bin/winetricks \
    # create directory for wineprefix and set ownership to jenkins user
    && mkdir -p -m 771 usr/wine \
    && chown jenkins:jenkins usr/wine \
    # steps to download cmake in wine
    && export WINEARCH=win64 \
    && wget ${CMAKELINK}${CMAKEWINDOWSFILE}

USER jenkins

# install jenkins plugins
COPY --chown=jenkins:jenkins plugins.txt /usr/share/jenkins/ref/plugins.txt
RUN jenkins-plugin-cli -f /usr/share/jenkins/ref/plugins.txt \
  # set wine default version as Windows 10
  && WINEPREFIX=/usr/wine/.wine xvfb-run -a winetricks -q win10 \
  # install cmake in wine
  && WINEPREFIX=/usr/wine/.wine xvfb-run -a wine msiexec -i ${CMAKEWINDOWSFILE} -q

# 'create' the unstable app pipeline job by copying its config
COPY /tdd_simplemockhelper_job.xml /usr/share/jenkins/ref/jobs/tdd_simplemockhelper_job/config.xml
