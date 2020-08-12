ubuntu_mirror = 'http://ubuntu.mirror.rafal.ca/ubuntu/'
ubuntu_release = 'bionic'
ubuntu_version = '18.04'
username = 'vagrant'
user_home = '/home/' + username
project_home = user_home + '/project/demos' # you may need to change the working directory to match your project


python3_packages = '/usr/local/lib/python3.6/dist-packages'
ruby_gems = '/var/lib/gems/2.5.0/gems/'


# Get Ubuntu sources set up and packages up to date.

template '/etc/apt/sources.list' do
  variables(
    :mirror => ubuntu_mirror,
    :release => ubuntu_release
  )
  notifies :run, 'execute[apt-get update]', :immediately
end
execute 'apt-get update' do
  action :nothing
end
execute 'apt-get upgrade' do
  command 'apt-get dist-upgrade -y'
  only_if 'apt list --upgradeable | grep -q upgradable'
end
directory '/opt'
directory '/opt/installers'


# Basic packages many of us probably want. Includes gcc C and C++ compilers.

package ['build-essential', 'cmake']


# Other core language tools you might want

package ['python3', 'python3-pip', 'python3-dev']  # Python
#package ['ghc', 'libghc-random-dev', 'cabal-install']  # Haskell
#package 'golang-go'  # Go
#package 'erlang'  # Erlang
#package 'ocaml-nox'  # OCaml
#package ['rustc', 'cargo']  # Rust
#package 'scala'  # Scala
#package ['ruby', 'ruby-dev']  # Ruby
#package ['openjdk-11-jdk', 'maven']  # Java
#package ['php-cli', 'php-pear']  # PHP
package 'clang' # Clang C/C++ compiler
execute 'pip3 install Flask'

# .NET Core

#remote_file '/opt/installers/packages-microsoft-prod.deb' do
#  source "https://packages.microsoft.com/config/ubuntu/#{ubuntu_version}/packages-microsoft-prod.deb"
#end
#execute 'dpkg -i /opt/installers/packages-microsoft-prod.deb' do
#  creates '/etc/apt/sources.list.d/microsoft-prod.list'
#  notifies :run, 'execute[apt-get update]', :immediately
#end
#package ['dotnet-sdk-3.1']


# NodeJS (more modern than Ubuntu nodejs package) and NPM

#remote_file '/opt/installers/node-setup.sh' do
#  source 'https://deb.nodesource.com/setup_14.x'
#  mode '0755'
#end
#execute '/opt/installers/node-setup.sh' do
#  creates '/etc/apt/sources.list.d/nodesource.list'
#  notifies :run, 'execute[apt-get update]', :immediately
#end
#package ['nodejs']


# SWIG

#package 'swig'


# RabbitMQ-related things

#package ['rabbitmq-server']

# Python pika library
#execute 'pip3 install pika==1.1.0' do
#  creates "#{python3_packages}/pika/__init__.py"
#end
# Ruby bunny library
#execute 'gem install bunny -v 2.15.0' do
#  creates "#{ruby_gems}/bunny-2.15.0/Gemfile"
#end
# Go amqp library
#execute 'go get github.com/streadway/amqp github.com/google/uuid' do
#  cwd project_home 
#  user username
#  environment 'HOME' => user_home
#  creates user_home + '/go/src/github.com/streadway/amqp/README.md'
#end
# Java amqp library
#package 'librabbitmq-client-java'


# ZeroMQ-related things

# C/C++ library and dev library
#package ['libzmq5', 'libzmq5-dev']
# Python pyzmq library
#execute 'pip3 install pyzmq==19.0.1' do
#  creates "#{python3_packages}/zmq/__init__.py"
#end
# Ruby ezmq library
#execute 'gem install ezmq -v 0.4.12' do
#  creates "#{ruby_gems}/ezmq-0.4.12/Gemfile"
#end
# Node zmq library
#execute 'npm install zeromq@6.0.0-beta.6' do
#  cwd project_home
#  user username
#  environment 'HOME' => user_home
#  creates project_home + '/node_modules/zeromq/package.json'
#end
# Go zmq4 library
#execute 'go get github.com/pebbe/zmq4' do
#  cwd project_home 
#  user username
#  environment 'HOME' => user_home
#  creates user_home + '/go/pkg/linux_amd64/github.com/pebbe/zmq4.a'
#end


# GraalVM

#graalvm_version = '20.1.0'
#graalvm_directory = "graalvm-ce-java11-#{graalvm_version}"
#remote_file '/opt/installers/graalvm.tar.gz' do
#  source "https://github.com/graalvm/graalvm-ce-builds/releases/download/vm-#{graalvm_version}/graalvm-ce-java11-linux-amd64-#{graalvm_version}.tar.gz"
#end
#execute 'tar zxf /opt/installers/graalvm.tar.gz' do
#  cwd '/opt'
#  creates "/opt/#{graalvm_directory}/release"
#end
#link '/opt/graalvm' do
#  to "/opt/#{graalvm_directory}"
#  link_type :symbolic
#end
#file '/etc/profile.d/graalvm.sh' do
#  content 'PATH=${PATH}:/opt/graalvm/bin'
#end
# GraalVM's Python
#execute '/opt/graalvm/bin/gu install python' do
#  creates "/opt/#{graalvm_directory}/bin/graalpython"
#end
# GraalVM's Ruby
#execute '/opt/graalvm/bin/gu install ruby' do
#  creates "/opt/#{graalvm_directory}/bin/ruby"
#end
# GraalVM's LLVM (C, C++) tools
#execute '/opt/graalvm/bin/gu install llvm-toolchain' do
#  creates "/opt/#{graalvm_directory}/bin/lli"
#end
