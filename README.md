# Labs Platform Core

This is Labs Platform Core. It's a library containing basic tools for building object-oriented applications in a cross-platform manner; in particular, it provides:

* Basic data structures;
* Clear ownership rules;
* Ease of building;
* An eye on bridging;
* Almost no dependencies (it depends only on `libpthread` and a few POSIX types).

This library is **NOT**:

* Efficient;
* Idiomatic C++;
* Beautiful by any metric.

**THIS LIBRARY IS IN PRE-ALPHA STATE. IT'S NOT SHIPPING. IT MAY CONTAIN TONS OF BUGS (including concurrency bugs — the worst kind EVER).** That said, I fully intend to use it as a foundation on my cross-platform applications going forward, so it can only get better.

## Building the Core

The Core is designed to be packaged as a **private** library in a shipped application. "Private" here means that there is no focus on a stable ABI; the sources can be used to produce a shared library, but the library is **NOT** designed to be replaced seamlessly with a later version — if you package it as a shared library, you must ensure only your application uses it. Typically, you won't go jump through all these hoops; you'll package Platform Core as a static library, or even just add the sources to your application and build 'em.

One of the invariants of Platform Core is that it can be built by simply compiling all `IL*.cpp` files alongside an application. No build tools, no configuration step, nothing, nada. `gcc IL*.cpp MyApp.cpp -o MyApp`. Nothing more.

That said, there are two built-in ways to build the Core:

* The Xcode project produces a dynamic library. It's notable as one of the targets in the project allows you to run unit tests on the code. (For now, tests are built using the OCUnit test framework that is built into Apple's tools.)

* The included Makefile can produce static and dynamic libraries out of the code. It's flexible enough to be adapted to basically any platform GCC can produce code for. (Sample platform variants are included for Darwin, Google's Native Client SDK and the Palm webOS PDK.) Example of use:

		make PLATFORM=Darwin.mk
	
	The default platform name is equal to the result of the `uname` tool (so, on Mac OS X it's `Darwin` by default).

## Using the Core

Documentation on the library is forthcoming. However, a primer:

* Include `Argyle.h` (name subject to change in the future) in your code. Do not include other `.h` files.

* Before you can call any of the code, you must create a ILReleasePool object on the stack. Just stick:

		ILReleasePool pool;
	
	at the top of your scope. This is not required in callbacks that have been called by Platform Core code.

* Interesting objects in this library all derive from ILObject. To create one, just use the constructor normally — note that instances of all classes derived from ILObject **must** be created on the heap (with the `new` operator). For example:

		ILList* l = new ILList();
		// Use l freely.
		
* To keep an object alive past the current function, you must retain it using the ILRetain function. When you're done using it, release it using the ILRelease function. For example:

		SomeClass::SomeClass() {
			this->_aList = ILRetain(new ILList()); // will remain valid past the end of this constructor.
		}
		
		SomeClass::~SomeClass() {
			ILRelease(this->_aList); // we don't need it anymore.
		}
		
	This reference counting scheme works exactly like Cocoa's or Core Foundation's memory management rules, with release pool objects taking the place of NSAutoreleasePools from Cocoa. The main differences are that no method and no constructor is 'special' -- you only release what you retain. (In Cocoa, methods with `alloc`/`init`, `copy` and `new` in their names require you to release later.)

## License

Platform Core is in the public domain:

<p xmlns:dct="http://purl.org/dc/terms/" xmlns:vcard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <a rel="license" href="http://creativecommons.org/publicdomain/zero/1.0/">
    <img src="http://i.creativecommons.org/l/zero/1.0/88x31.png" style="border-style: none;" alt="CC0" />
  </a>
  <br />
  To the extent possible under law, <a href="http://infinite-labs.net/me/" rel="dct:publisher"><span property="dct:title">Emanuele Vulcano</span></a>
  has waived all copyright and related or neighboring rights to
  <span property="dct:title">Labs Platform Core ("Argyle")</span>.
This work is published from
<span about="http://infinite-labs.net/me/" property="vcard:Country" datatype="dct:ISO3166" content="IT">Italy</span>.
</p>

