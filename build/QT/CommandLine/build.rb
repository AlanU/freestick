require 'fileutils'
require 'os'
require 'zip'

BUILD_DIR = 'temp'
TEST_APP_BUILD_DIR = 'JoyStickConfig'
OUT_DIR = 'out'
HEADER_PATH = '../../../inc'
VISUAL_STUDIO_PATH = 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build'
QT_DEPLOAY_ARGS="-qmldir=../JoyStickConfig"
def self.sh (command, command_display_override = nil)
  result, output = sh_output_result(command, command_display_override)
  return result
end

def self.sh_output (command, command_display_override = nil)
  result, output = self.sh_output_result(command, command_display_override = nil)
  return output
end

def self.sh_output_result(command, command_display_override = nil)
  puts "*** Running ***"
  display_command = command
  if (command_display_override != nil)
    display_command = command_display_override
  end
  puts display_command
  output = `#{command}`
  result = $?.success?
  if result
    puts output if !!ENV['SFVERBOSE'] == true
    puts "*** Completed #{display_command}"
  else
    puts "Failed"
    puts output
  end
  return result, output
end


def build(qtPath, spec , makePath, configString, qmakeProFile)
  # TODO make user there is a way for android to copy java files
  qmake_command = "#{qtPath}/bin/qmake #{qmakeProFile} -r -spec #{spec} #{configString}"
  make_command = "#{makePath}"
  if  OS.windows?
    vs_command ="\"#{VISUAL_STUDIO_PATH}/vcvarsall.bat\" x86_amd64"
    qmake_command = "#{vs_command} && " + qmake_command
    make_command = "#{vs_command} && " + make_command
  end
  qmake_results = sh "#{qmake_command}"
  build_results = sh "#{make_command}"
  return qmake_results && build_results
end

def deploy_qt(qt_path, qt_compiler, app_path)
  if OS.linux?
    puts "**** Linux Builds Not Supported ****"
  elsif OS.windows?
    puts "**** Windows Builds Not Supported ****"

    #windeployqt="#{APP.build_system.path}/#{APP.qt_version}/#{APP.build_system.folder}/bin/windeployqt"
    # result = BuildUtils.sh("#{windeployqt} \"#{app_path}/Slash N Forge.exe\" #{APP.build_system.deploy_args}")
    # unless result
    #   raise "Windeployqt Error"
    # end
    #FileUtils.cp_r("#{APP.windows_external_dependencies}/.","#{app_path}")
    # FileUtils.cp_r("#{APP.windows_external_dependencies}/.","#{app_path}")
    #FileUtils.cp_r("#{APP.lib_folder}/lexactivator/3.9.0/win32/x64/dll/.","#{app_path}")
  elsif OS.mac?
    puts "****** Running Macdeployqt *******"
    macdeployqt="#{qt_path}/#{qt_compiler}/bin/macdeployqt"
    result = sh("#{macdeployqt} '#{app_path}' #{QT_DEPLOAY_ARGS}")
    unless result
      raise "Macdeployqt Error"
    end
  end
end

def copyArtifacts(outputName, input_dir)
  FileUtils.rm_rf(OUT_DIR)
  Dir.mkdir(OUT_DIR)
  Dir.chdir(OUT_DIR)
  pwd = Dir.pwd
  #FileUtils.cp_r("../#{HEADER_PATH}", "../#{input_dir}/release")
  # File.rename("./#{BUILD_DIR}", outputName )
  input_Dir = "../#{input_dir}/release"
  ::Zip::File.open("#{outputName}.zip", ::Zip::File::CREATE) do |zipFile|
    Dir["#{input_Dir}/**/**"].each do |file|
      # unless (file == 'release')
        zipFile.add(file.sub(input_Dir + '/', ''), file)
      # end
    end
  end
end

$build_target = ''
$qt_path = ''
$build_test_app = false
def processArgs()
  ARGV.each do |arg|
    commands = arg.split('=')
    if(commands.length < 2 )
      break;
    end
    command = commands[0].delete('-')
    value =  commands[1].delete("'").delete('"')
    case command
    when 'build_test_app'
      $build_test_app = true
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
  qt_compiler = 'win64_msvc2019_64'
  config_string = 'CONFIG+=qtquickcompiler'
  make_path = "C:/Qt/Tools/QtCreator/bin/jom.exe" # TODO use passed in path
  out_put_file_name = 'windows64'
end

if spec.empty? && qt_compiler.empty? && config_string.empty?
  exit -1
else
  lib_build_results = build("#{$qt_path}/#{qt_compiler}", "#{spec}", make_path, config_string, '../../FreeStick/FreeStick.pro')
  if($build_test_app)
    # TODO Fix Building test App
    test_app_build_results = build("#{$qt_path}/#{qt_compiler}", "#{spec}", make_path, config_string, '../../FreeStickTestApp/FreeStickTestApp.pro')
  end
  Dir.chdir('..')
  deploy_qt($qt_path, qt_compiler, './JoyStickConfig/release/JoyStickConfig.app') if($build_test_app)
  FileUtils.cp_r("#{HEADER_PATH}", "#{BUILD_DIR}/release") #copy headers over
  copyArtifacts(out_put_file_name, BUILD_DIR)
  copyArtifacts('joystickConfig', TEST_APP_BUILD_DIR) if($build_test_app)
  exit -1 unless lib_build_results # && test_app_build_results
end
