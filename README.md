# TDD_SimpleMockHelper

This contains different test to show use cases of SimpleMockHelper which is a way of mocking methods.
Still I think many issues could be hidden because it is a toy project.
It contains a mini CI local environment that when the docker image is running, each local commit triggers Jenkins to compile the code for linux and Windows, then run some tests (using Wine for the windows program) to see if that commit succeeds/fails.

To start developing, use:

- Run sudo systemctl start docker (to start the docker daemon)
- Run ./add_post_commit_hook.sh (but first make sure it is set as executable program)
- Run 'docker compose up' to spin up the project and 'docker compose up --build' if you made changes to the Dockerfile. Or use docker compose up --force-recreate to recreate the container if some copy problems arise.
- Once Jenkins is fully up and running you will be able to commit and Jenkins will run a local job to automatically test your modifications (check http://localhost:8080/job/tdd_simplemockhelper_job/ to see the job results each time you commit).

(if you change your job in jenkins, remember to copy its config.xml into tdd_simplemockhelper_job.xml, for example http://localhost:8080/job/tdd_simplemockhelper_job/config.xml)

In fedora, it is possible that you will need to
sudo setenforce 0
