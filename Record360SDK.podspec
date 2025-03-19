Pod::Spec.new do |s|
	s.name                  = 'Record360SDK'
	s.version               = '4.17.2'
	s.summary               = 'Record360 SDK'
	s.description           = <<-DESC
		Record360 is a high-quality property condition reporting tool.  Use this SDK to integrate our damage documentation and dispute resolution tool.
	DESC

	s.homepage             	= 'https://www.record360.com'
	s.license               = { :type => 'commercial', :file => 'LICENSE' }
	s.authors               = {
		'Alexis Valencia' => 'alex@record360.com',
		'Tobin Pomeroy' => 'tpomeroy@record360.com'
	}
	s.source              	= { :git => 'https://github.com/Record360/record360-sdk-ios.git', :tag => s.version.to_s }

	s.ios.deployment_target = '14.0'

	s.dependency 'AFNetworking', '4.0.1'
	s.dependency 'CocoaLumberjack', '3.7.4'
	s.dependency 'Realm', '10.25.0'
	s.dependency 'Analytics', '4.1.6'
	s.dependency 'Segment-Amplitude', '3.2.3'

	s.ios.frameworks = 'Accelerate', 'AssetsLibrary', 'AudioToolbox', 'AVFoundation', 'CoreGraphics', 'CoreLocation', 'CoreMedia', 'CoreMotion', 'CoreText', 'CoreVideo', 'ImageIO', 'QuartzCore', 'SystemConfiguration'

	s.ios.libraries = 'iconv', 'c++', 'z'

	s.ios.vendored_frameworks = 'Record360SDK.framework'
	s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
	s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

end
