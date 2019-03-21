Pod::Spec.new do |s|

	s.name                  = 'Record360SDK'
	s.version               = '1.6.0'
	s.summary               = 'Record360 SDK'
	s.description           = <<-DESC
		Record360 is a high-quality property condition reporting tool.  Use this SDK to integrate our damage documentation and dispute resolution tool.
	DESC

	s.homepage             	= 'https://www.record360.com'
	s.license               = { :type => 'commercial', :file => 'LICENSE' }
	s.authors               = {
		'Justin Friberg' => 'justin@record360.com',
		'Alexis Valencia' => 'alex@record360.com'
	}
	s.source              	= { :git => 'https://github.com/Record360/record360-sdk-ios.git', :tag => s.version.to_s }

	s.ios.deployment_target = '10.0'

	s.dependency 'AFNetworking', '3.2.0'
	s.dependency 'CocoaLumberjack', '3.4.1'
	s.dependency 'MBProgressHUD', '1.1.0'
	s.dependency 'Realm', '3.1.0'
	s.dependency 'ZXingObjC', '3.2.2'

	s.ios.frameworks = 'Accelerate','CoreLocation','ImageIO','CoreText','CoreMotion','SystemConfiguration','AssetsLibrary','AudioToolbox','AVFoundation','CoreMedia','CoreVideo','CoreGraphics','QuartzCore'

	s.ios.libraries = 'iconv', 'c++', 'z'

	s.ios.vendored_frameworks = 'Record360SDK.framework'

end
