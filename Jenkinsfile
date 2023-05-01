pipeline {
    agent any

    stages {
        stage('Preparation'){
            steps {
                echo 'Cleaning up workspace:'
                echo '-Checking current workspace:'
                sh 'ls'
                sh 'git reset --hard'//resets to HEAD, to the commit in the cloned repository.
                sh 'git clean -dffx .'//removes untracked files.
                echo '-Checking clean workspace:'
                sh 'ls'
            }
        }

        stage('Build') {
            parallel {
                stage('Build for Linux') {
                    steps {
                        echo 'Starting compilation for linux platform\n'
                        sh 'bash build_with_cmake_linux.sh'
                        echo '\n Finished compilation for linux platform\n'
                    }
                }
                stage('Build for Windows') {
                    steps {
                        echo 'Starting compilation for windows platform\n'
                        sh 'bash build_with_cmake_windows.sh'
                        echo '\n Finished compilation for windows platform\n'
                        
                    }
                }
            }
        }

        stage('Test'){
            parallel {
                stage ('Linux test') {
                    steps {
                        script {
                            echo 'Starting testing for linux platform\n'
                            sh 'bash test_with_ctest_linux.sh'
                            echo '\n Finished testing for windows platform\n'
                        }
                    }
                }
                stage ('Windows test') {
                    steps {
                        script {
                            echo 'Starting testing for windows platform\n'
                            sh 'bash test_with_ctest_windows.sh'
                            echo '\n Finished testing for windows platform\n'
                        }
                    }
                }
            }
        }
    }
    post {
        always {
            echo 'Publishing JUnit test report'
            junit 'junit_report.xml'
        }
    }
}
