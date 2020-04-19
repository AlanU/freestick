pipeline {
  agent none
  stages {
    stage('Build') {
      parallel {
        stage ('Mac') {
            agent { label 'Mac' }
            stages {
                stage('Build Mac') {
                  steps {
                    dir(path: './build/QT/CommandLine') {
                      sh 'gem install bundler'
                      sh 'bundle install'
                      sh 'ruby build.rb --qt=/Users/Shared/Qt/5.13.2 --target=mac'
                    }
                  }
                }
                stage('Copy Artifacts Mac') {
                    steps {
                        archiveArtifacts artifacts: 'build/QT/CommandLine/out/*.zip', fingerprint: true
                    }
                }
                
            }
        }
        stage('Windows') {
            agent { label 'Windows' }
            stages {
                stage('Build Windows') {
                      steps {
                        dir(path: './build/QT/CommandLine') {
                          bat 'gem install bundler'
                          bat 'bundle install'
                          bat 'ruby build.rb --qt=C:\\Qt\\5.13.2\\ --target=windows'
                        }
                      }
                }
                stage('Copy Artifacts Windows') {
                  steps {
                      archiveArtifacts artifacts: 'build/QT/CommandLine/out/*.zip', fingerprint: true
                  }
                }
            }
        }
        stage ('iOS')
        {
            agent {
             label 'iOS'
            }
            stages {
                stage('Build iOS') {
                  steps {
                    dir(path: './build/QT/CommandLine') {
                      sh 'gem install bundler'
                      sh 'bundle install'
                      sh 'ruby build.rb --qt=/Users/Shared/Qt/5.13.2 --target=ios'
                    }
                  }
                }
                stage('Copy Artifacts iOS') {
                    steps {
                        archiveArtifacts artifacts: 'build/QT/CommandLine/out/*.zip', fingerprint: true
                    }
                }
            }
        }
      }
    }
  }
}
