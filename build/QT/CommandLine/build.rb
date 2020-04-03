require 'fileutils'
require 'os'
require 'zip'

BUILD_DIR = 'temp'
OUT_DIR = 'out'
HEADER_PATH = '../../../inc'
VISUAL_STUDIO_PATH = 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build'
def build(qtPath, spec , makePath, configString, qmakeProFile)
  # TODO make user there is a way for android to copy java files
  qmake_command = "#{qtPath}/bin/qmake #{qmakeProFile} -r -spec #{spec} #{configString}"
  make_command = "#{makePath}"
  if  OS.windows?
    vs_command ="\"#{VISUAL_STUDIO_PATH}/vcvarsall.bat\" x86_amd64"
    qmake_command = "#{vs_command} && " + qmake_command
    make_command = "#{vs_command} && " + make_command
  end
  qmake_results = system "#{qmake_command}"
  build_results = system "#{make_command}"
  return qmake_results && build_results
end


def copyArtifacts(outputName)
  FileUtils.rm_rf(OUT_DIR)
  Dir.mkdir(OUT_DIR)
  Dir.chdir(OUT_DIR)
  pwd = Dir.pwd
  FileUtils.cp_r("../#{HEADER_PATH}","../#{BUILD_DIR}/release")
  #File.rename("./#{BUILD_DIR}", outputName )
  input_Dir = "../#{BUILD_DIR}/release"
  ::Zip::File.open("#{outputName}.zip", ::Zip::File::CREATE) do |zipFile|
    Dir["#{input_Dir}/**/**"].each do |file|
      #unless (file == 'release')
        zipFile.add(file.sub(input_Dir + '/', ''), file)
      #end
    end
  end
end

$build_target = ''
$qt_path = ''

def processArgs()
  ARGV.each do |arg|
    commands = arg.split('=')
    if(commands.length < 2 )
      break;
    end
    command = commands[0].delete('-')
    value =  commands[1].delete("'").delete('"')
    case command
    when 'qt'
      $qt_path = value
    when 'target'
      $build_target = value.downcase()
    end

  end
end

processArgs()

FileUtils.rm_rf(BUILD_DIR)
Dir.mkdir(BUILD_DIR)
Dir.chdir(BUILD_DIR)

# Test Mac

make_path = 'make'
spec = ''
qt_compiler = ''
config_string = ''
out_put_file_name = ''

case $build_target
when 'mac'
  spec = 'macx-clang'
  qt_compiler = 'clang_64'
  config_string = 'CONFIG+=x86_64'
  out_put_file_name = 'macOSX'
when 'ios'
  spec = 'macx-ios-clang'
  qt_compiler = 'ios'
  config_string = 'CONFIG+=release CONFIG+=iphoneos CONFIG+=device CONFIG+=qtquickcompiler -after'
  out_put_file_name = 'iOS'
when 'windows'
  spec = 'win32-msvc'
  qt_compiler = 'msvc2017_64'
  config_string = 'CONFIG+=qtquickcompiler'
  make_path = "C:/Qt/Tools/QtCreator/bin/jom.exe" #TODO use passed in path
  out_put_file_name = 'windows64'
end


unless spec.empty? && qt_compiler.empty? && config_string.empty?
  lib_build_results = build("#{$qt_path}/#{qt_compiler}","#{spec}",make_path, config_string,'../../FreeStick/FreeStick.pro')
  #TODO Fix Building test App
  #test_app_build_results = build("#{$qt_path}/#{qt_compiler}","#{spec}",make_path, config_string,'../../FreeStickTestApp/FreeStickTestApp.pro')
  Dir.chdir('..')
  copyArtifacts(out_put_file_name)
  unless lib_build_results # && test_app_build_results
    exit -1
  end
else
  exit -1
end
