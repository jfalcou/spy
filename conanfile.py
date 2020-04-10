import os

from conans import ConanFile, tools
class SpyConan(ConanFile):
    name = "spy"
    settings = "os", "compiler", "build_type", "arch"
    version = "0.0.3"
    license = "MIT"
    author = "Joel FALCOU joel.falcou@compilaction.net"
    url = "https://github.com/jfalcou/spy.git"
    homepage = "https://jfalcou.github.io/spy/"
    description = "C++ 17 for constexpr-proof detection and classification of informations about OS, compiler, etc..."
    topics = ("c++17", "config", "metaprogramming")
    no_copy_source = True
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }

    def package(self):
        self.copy("LICENSE", "licenses")
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
