Pod::Spec.new do |s|

	s.name                  = 'Record360SDK'
	s.version               = '1.1.0'
	s.summary               = 'Record360 SDK'
	s.description           = <<-DESC
		Record360 is a high-quality property condition reporting tool.  Use this SDK to integrate our damage documentation and dispute resolution tool.
	DESC

	s.homepage             	= 'https://www.record360.com'
	s.license               = { :type => 'commercial', :file => 'LICENSE' }
	s.authors               = {
		'Justin Friberg' => 'justin@record360.com',
		'Brandon Charity' => 'brandon@record360.com'
	}
	s.source              	= { :git => 'https://github.com/Record360/record360-sdk-ios.git', :tag => s.version.to_s }

	s.ios.deployment_target = '9.0'

	s.dependency 'AFNetworking', '3.1.0'
	s.dependency 'CocoaLumberjack', '3.0.0'
	s.dependency 'GPUImage', '0.1.7'
	s.dependency 'MBProgressHUD', '1.0.0'
	s.dependency 'Realm', '2.10.1'
	s.dependency 'ZXingObjC', '3.2.1'

	s.ios.frameworks = 'Accelerate','CoreLocation','ImageIO','CoreText','CoreMotion','SystemConfiguration','AssetsLibrary','AudioToolbox','AVFoundation','CoreMedia','CoreVideo','CoreGraphics','QuartzCore'

	s.ios.libraries = 'iconv', 'c++', 'z'

	s.ios.vendored_frameworks = 'Record360SDK.framework'

end
