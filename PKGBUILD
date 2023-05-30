# Maintainer: Luka287 <Luka287@proton.me>

pkgname=ced 
pkgver=0.7.7
pkgrel=1
epoch=
pkgdesc="Simple text editor made with Qt"
arch=('any')
url="https://github.com/Luka287/ced.git"
license=('GPL3')
groups=()
depends=(qt6-base)
makedepends=('cmake' 'ninja')
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("https://github.com/Luka287/ced/archive/refs/tags/${pkgver}.tar.gz")
noextract=()
md5sums=()
validpgpkeys=()

build(){
	cd "$pkgname-$pkgver"
	
	cmake .

	cmake --build . --target all
}

package(){
	cd "$pkgname-$pkgver"

	install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
	install -Dm644 README.md "${pkgdir}/usr/share/doc/${pkgname}/README.md"
	install -Dm644 ced.desktop "${pkgdir}/usr/share/applications/ced.desktop"

	install -Dm755 ced "${pkgdir}/usr/bin/ced"

	install -Dm644 config.json "${pkgdir}/etc/ced/config.json"
	install -Dm666 config.json "${pkgdir}/$HOME/.config/ced/config.json"

	install -Dm644 ced.png "${pkgdir}/usr/share/pixmaps/ced.png"
}



sha256sums=('95f784bc0c72ef90d09a65e9eda621bd213c491f93a9631630b7a7730283bb95')
