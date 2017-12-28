# Color

```js
/**
 * hexToRgb
 * @param {string} - hex - hexadecimal color code
 * @return {string} - rgb(r,g,b)
 */
const hexToRgb = hex => {
    let _hex = /^#/.test(hex) ? hex.slice(1) : hex
    if(/^(3|6)$/.test(_hex.length)) {
        let h = parseInt(_hex.length === 3
            // Array.prototype.map.call()
            ? [..._hex].map(i => i + i).join('')
            : _hex, 16)
        return  `rgb(${h >> 16}, ${(h & 0x00ff00) >> 8}, ${h & 0x0000ff})`
    } else {
        console.error('Invalid color value! Parameter rules: range: (0-9 a-f A-F), color code: 3-digit or 6-digit')
    }
}
hexToRgb('acd') // "rgb(170, 204, 221)"
hexToRgb('#aaccdd') // "rgb(170, 204, 221)"
hexToRgb('adec') // 'Invalid color value! ...'

/**
 * rgbToHex
 * @param {number} - r : 0 ~ 255
 * @param {number} - g : 0 ~ 255
 * @param {number} - b : 0 ~ 255
 * @return {string} - hexadecimal color code
 */
const rgbToHex = (r, g, b) => {
    const isRange = val => 0 <= val && val <= 255
    return isRange(r) && isRange(g) && isRange(b)
        ? '#' + ((r << 16) + (g << 8) + b).toString(16).padStart(6, '0')
        : console.error('Invalid color value! Parameter rules: value range: (0-255)')
}
rgbToHex(240, 167, 3) // '#f0a703'
rgbToHex(0, 0, 255) // '#0000ff'
rgbToHex(0, 256, 255) // 'Invalid color value! ...'
```

![hexToRgb console error](/img/js/hextorgb.png)
![rgbToHex console error](/img/js/rgbtohex.png)

[[↻ Back To Home](/README.md)] &nbsp;
[[☝︎ Back To TOP](#color)]