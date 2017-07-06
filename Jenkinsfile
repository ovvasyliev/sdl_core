
agent { node { label 'atf_slave' } } 

stages {
		stage ("Code Style Check")
		{
			steps
			{
			sh 'bash tools/infrastructure/check_style.sh'
			}
		}
    parallel (
    'C' : { 
		agent { node { label 'atf_slave2' } } 
		stage ('Build')
		{
			steps
			{
			checkout scm
			sh '''
			rm -rf build
			mkdir build
			cd build
			export THIRD_PARTY_INSTALL_PREFIX=${WORKSPACE}/build/src/3rdparty/LINUX
			export THIRD_PARTY_INSTALL_PREFIX_ARCH=${THIRD_PARTY_INSTALL_PREFIX}/x86
			export LD_LIBRARY_PATH=$THIRD_PARTY_INSTALL_PREFIX_ARCH/lib
			cmake ${WORKSPACE} -DCMAKE_BUILD_TYPE="Debug" -DBUILD_TESTS=ON -DENABLE_GCOV=ON -DREMOTE_CONTROL=ON
			make install'''	
			}
		}

		stage ('Unit Testing')
		{
			steps
			{
			sh '''#!/bin/bash
			cd build
			make test | tee ut.log || true; result=${PIPESTATUS[0]};
			if [ $result -ne 0 ]; then
			COREFILE=$(find /tmp/corefiles -type f -name "core*");
			echo $COREFILE;
			grep -w "SegFault" ut.log | while read -r line; do 
				arr=($line); 
				echo ${arr[3]};
			done > res.txt;
			test_file=$(find ${WORKSPACE}/build/src/components/ -type f -name $(cat res.txt));
			echo $test_file;
			echo "Started gdb!";
			echo thread apply all bt | gdb $test_file $COREFILE;
			exit 1;
			fi'''
			}
		}
		},
		'D': {
			agent { node { label 'atf_slave2' } } 
			stage ('Build')
		{
			steps
			{
			checkout scm
			sh '''
			rm -rf build
			mkdir build
			cd build
			export THIRD_PARTY_INSTALL_PREFIX=${WORKSPACE}/build/src/3rdparty/LINUX
			export THIRD_PARTY_INSTALL_PREFIX_ARCH=${THIRD_PARTY_INSTALL_PREFIX}/x86
			export LD_LIBRARY_PATH=$THIRD_PARTY_INSTALL_PREFIX_ARCH/lib
			cmake ${WORKSPACE} -DCMAKE_BUILD_TYPE="Debug" -DBUILD_TESTS=ON -DENABLE_GCOV=ON -DREMOTE_CONTROL=ON
			make install'''	
			}
		}

		stage ('Unit Testing')
		{
			steps
			{
			sh '''#!/bin/bash
			cd build
			make test | tee ut.log || true; result=${PIPESTATUS[0]};
			if [ $result -ne 0 ]; then
			COREFILE=$(find /tmp/corefiles -type f -name "core*");
			echo $COREFILE;
			grep -w "SegFault" ut.log | while read -r line; do 
				arr=($line); 
				echo ${arr[3]};
			done > res.txt;
			test_file=$(find ${WORKSPACE}/build/src/components/ -type f -name $(cat res.txt));
			echo $test_file;
			echo "Started gdb!";
			echo thread apply all bt | gdb $test_file $COREFILE;
			exit 1;
			fi'''
			}
		}})	
		stage ('Parallel')
		{
			steps
			{
						parallel(
						Packaging: 
						{
							sh '''cp -r ${WORKSPACE}/build/src/3rdparty/LINUX/x86/lib/. ${WORKSPACE}/build/bin/
							mkdir ${WORKSPACE}/build/bin/api
							cp -r ${WORKSPACE}/src/components/interfaces/. ${WORKSPACE}/build/bin/api/
							tar -zcvf OpenSDL_${TESTS}.tar.gz bin/
							curl -u admin:1qaz@WSX -X PUT "http://172.30.23.4:8081/artifactory/OpenSDL_${GIT_BRANCH}/${BUILD_NUMBER}/${RC}/OpenSDL_${TESTS}.tar.gz" -T OpenSDL.tar.gz'''
						},
						Cppcheck: 
						{
							sh '''cppcheck --enable=all --inconclusive -i "src/3rd_party-static" -i "src/3rd_party" --xml --xml-version=2 -q src 2> cppcheck.xml'''
						},
						Artifacts: 
						{
							junit allowEmptyResults: true, testResults: '${WORKSPACE}/build/test_results/*.xml'
						})
			}
		}
}
		post {
				// Always runs. And it runs before any of the other post conditions.
				always {
					// Let's wipe out the workspace before we finish!
					deleteDir()
				}
				
				success {
					emailext attachLog: true, body: '${SCRIPT, template="groovy-html.template"}', recipientProviders: [[$class: 'DevelopersRecipientProvider']], replyTo: 'mailer@lc-jenkinsdockerhost.luxoft.com', subject: '', to: 'AKutsan@luxoft.com, MGhiumiusliu@luxoft.com, IIKovalenko@luxoft.com, OVVasyliev@luxoft.com'
				}

				failure {
					emailext attachLog: true, body: '${SCRIPT, template="groovy-html.template"}', recipientProviders: [[$class: 'DevelopersRecipientProvider']], replyTo: 'mailer@lc-jenkinsdockerhost.luxoft.com', subject: '', to: 'AKutsan@luxoft.com, MGhiumiusliu@luxoft.com, IIKovalenko@luxoft.com, OVVasyliev@luxoft.com'
				}
			}