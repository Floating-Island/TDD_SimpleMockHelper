# Get the Official Jenkins Docker Image
FROM jenkins/jenkins:lts-jdk11
ENV JAVA_OPTS -Djenkins.install.runSetupWizard=false
# allow local checkout in git scm to be able to see local repository
ENV JAVA_OPTS -Dhudson.plugins.git.GitSCM.ALLOW_LOCAL_CHECKOUT=true

ARG CMAKE_VERSION=3.26.3

USER root
# install packages (including recommended) and dependencies
RUN apt-get update && apt-get -y install \
    build-essential \
    wget \
    gcc \
    g++ \
    mingw-w64 \
    python3 \
    # remove cache packages
    && rm -fr /var/lib/apt/lists/* \
    # install specific cmake version
    && wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /opt/cmake-${CMAKE_VERSION} \
      && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-${CMAKE_VERSION} \
      && rm /tmp/cmake-install.sh \
      && ln -s /opt/cmake-${CMAKE_VERSION}/bin/* /usr/local/bin




USER jenkins
# install jenkins plugins
COPY --chown=jenkins:jenkins plugins.txt /usr/share/jenkins/ref/plugins.txt
RUN jenkins-plugin-cli -f /usr/share/jenkins/ref/plugins.txt

# 'create' the unstable app pipeline job by copying its config
COPY /tdd_simplemockhelper_job.xml /usr/share/jenkins/ref/jobs/tdd_simplemockhelper_job/config.xml
