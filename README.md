Polyfills for missing functions on Mavericks. Intended to be used alongside [MacPorts Legacy Support](https://github.com/macports/macports-legacy-support); I only polyfill functions which MacPorts Legacy Support does not already provide.

To use this with a binary:

DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=/Path/To/libWowfunhappyLegacySupport.dylib:/Path/To/libMacportsLegacySupport.dylib /Path/To/Binary.

If your binary needs two-level namespacing, you'll have to do something more annoying like make libWowfunhappyLegacySupport re-export libSystem.B and then use install_name_tool to replace libSystem.B.dylib with libWowfunhappyLegacySupport.dylib. However, the fact that you also need to include libMacportsLegacySupport.dylib in the mix makes things complicated... so far I have not come across a situation where this is needed, whenever I do I guess I'll have to figure this out. 🙂
