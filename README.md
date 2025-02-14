# TDD_SimpleMockHelper

**DISCLAIMER:**
 You should not use this approach to mocking in C++ given that it is not possible to [convert a pointer to member function into void*](https://isocpp.org/wiki/faq/pointers-to-members#cant-cvt-memfnptr-to-voidptr). However, I liked how I combined a Jenkins Docker image with automatic CI check on each local commit.

This contains different test to show use cases of SimpleMockHelper which is a way of mocking methods.
It contains a mini CI local environment that when the docker image is running, each local commit triggers Jenkins to compile the code for linux and Windows, then run some tests (using Wine for the windows program) to see if that commit succeeds/fails.

To start developing, use:

- Run sudo systemctl start docker (to start the docker daemon)
- Run ./add_post_commit_hook.sh (but first make sure it's set as executable program)
- Run 'docker compose up' to spin up the project and 'docker compose up --build' if you made changes to the Dockerfile. Or use docker compose up --force-recreate to recreate the container if some copy problems arise.
- Once Jenkins is fully up and running you'll be able to commit and Jenkins will run a job to automatically test your modifications (check http://localhost:8080/job/tdd_simplemockhelper_job/ to see the job results each time you commit).

(if you change your job in jenkins, remember to copy its config.xml into tdd_simplemockhelper_job.xml, for example http://localhost:8080/job/tdd_simplemockhelper_job/config.xml)

In fedora, you could need to
sudo setenforce 0
