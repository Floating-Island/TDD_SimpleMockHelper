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
                echo '-checking clean workspace:'
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

        stage ('Linux test') {
            steps {
                script {
                    sh 'bash test_with_ctest_linux.sh'
                    // switch (statusCode) {
                    //     case 0:
                    //     break
                    //     case 1:
                    //     unstable ('Some tests failed. Setting stage and build as Unstable...')
                    //     break
                    //     default:
                    //         error("Error: tests returned with status code ${statusCode}")
                    //     break
                    // }
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
