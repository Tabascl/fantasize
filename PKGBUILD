pkgname=fantasize
pkgver=0.1.0
pkgrel=1
pkgdesc='C++ fan control for Linux'
url='https://github.com/Tabascl/fantasize.git'
source=("$pkgname-$pkgver.tar.gz::https://github.com/Tabascl/fantasize/archive/refs/tags/v$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('git' 'cmake' 'nlohmann-json' 'boost' 'cuda')
sha256sums=('69d61255edb49b66396f00b7bfadb39ce1220769838929ad74dc9f3301742ce7')

build() {
    cmake -S "$pkgname-$pkgver/app" -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
}

package() {
    cmake --install build --prefix "$pkgdir/" --verbose
}
