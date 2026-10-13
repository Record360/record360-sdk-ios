Pod::Spec.new do |s|
	s.name                  = 'Record360SDK'
	s.version               = '4.24.9'
	s.summary               = 'Record360 SDK'
	s.description           = <<-DESC
		Record360 is a high-quality property condition reporting tool.  Use this SDK to integrate our damage documentation and dispute resolution tool.
	DESC

	s.homepage             	= 'https://www.record360.com'
	s.license               = { :type => 'commercial', :file => 'LICENSE' }
	s.authors               = {
		'Alexis Valencia' => 'alex@record360.com',
		'John Detloff' => 'jdetloff@record360.com',
		'Ando Sonenblick' => 'ando.sonenblick@record360.com'
	}
	s.source              	= { :git => 'https://github.com/Record360/record360-sdk-ios.git', :tag => s.version.to_s }

	s.ios.deployment_target = '15.0'

	s.dependency 'CocoaLumberjack', '3.9.1'
	s.dependency 'Realm', '20.0.4'
	s.dependency 'Analytics', '4.1.8'
	s.dependency 'Segment-Amplitude', '3.2.3'
	s.dependency 'AppAuth', '2.0'

	s.ios.frameworks = 'Accelerate', 'AssetsLibrary', 'AudioToolbox', 'AVFoundation', 'CoreGraphics', 'CoreLocation', 'CoreMedia', 'CoreMotion', 'CoreText', 'CoreVideo', 'ImageIO', 'QuartzCore', 'SystemConfiguration'

	s.ios.libraries = 'iconv', 'c++', 'z'

	s.ios.vendored_frameworks = 'Record360SDK.framework'
	s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
	s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

end
