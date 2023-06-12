# TDD_SimpleMockHelper
Different test to show use cases of SimpleMockHelper

To start developing, use:

- Run sudo systemctl start docker (to start the docker daemon)
- Run ./add_post_commit_hook.sh (but first make sure it's set as executable program)
- Run 'docker compose up' to spin up the project and 'docker compose up --build' if you made changes to the Dockerfile. Or use docker compose up --force-recreate to recreate the container if some copy problems arise.
- Once Jenkins is fully up and running you'll be able to commit and Jenkins will run a job to automatically test your modifications (check http://localhost:8080/job/tdd_simplemockhelper_job/ to see the job results each time you commit).

(if you change your job in jenkins, remember to copy its config.xml into tdd_simplemockhelper_job.xml, for example http://localhost:8080/job/tdd_simplemockhelper_job/config.xml)

In fedora, you could need to
sudo setenforce 0