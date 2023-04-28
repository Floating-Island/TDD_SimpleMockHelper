# Get the Official Jenkins Docker Image
FROM jenkins/jenkins:lts-jdk11
ENV JAVA_OPTS -Djenkins.install.runSetupWizard=false

USER root
# install packages (including recommended) and dependencies
RUN apt-get update && apt-get -y install \
    cmake \
    gcc \
    g++ \
    mingw-w64 \
    python3 \
    # remove cache packages
    && rm -fr /var/lib/apt/lists/*

USER jenkins
# install jenkins plugins
COPY --chown=jenkins:jenkins plugins.txt /usr/share/jenkins/ref/plugins.txt
RUN jenkins-plugin-cli -f /usr/share/jenkins/ref/plugins.txt
    

# 'create' the unstable app pipeline job by copying its config
COPY /tdd_simplemockhelper_job.xml /usr/share/jenkins/ref/jobs/tdd_simplemockhelper_job/config.xml
