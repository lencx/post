# JavaScript Tricks

## Table of Contents

### *Concept*

* [`this`](/concept/this.zh.md)

### [*Color*](#color)

<details>

<summary>View contents</summary>

* [hexToRgb(), rgbToHex()](#hexcolor--rgb)
* [randomHexColor()](#random-hexcolor)

</details>

### [*Object*](#object)

<details>

<summary>View contents</summary>

* [*Object Has*](#object-has)
* [*Get Depth Object properties*](#get-depth-object-properties)

</details>

### [*Tools*](#tools)

<details>

<summary>View contents</summary>

* [*Checks Argument Type*](#checks-argument-type)
    > `isObj()`, `isArray()`, `isFunc()`, `isBool()`, `isRegExp()`
* [*String To Boolean*](#string-to-boolean)
* [*Set/Get localStorage*](#set-or-get-localstorage)
    > `setStorage()`, `getStorage()`
* [*Set/Get/Del Cookie*](#set-or-get-or-delete-cookie)
    > `setCookie()`, `getCookie()`, `delCookie()`
* [*Generated UUID*](#generated-uuid)
* [*Random HexColor*](#random-hexcolor)
* [*OrderBy*](#orderby)

</details>

### [*Math*](#math)

<details>

<summary>View contents</summary>

* [*Round*](#round)

</details>

### [*Array*](#array)

<details>

<summary>View contents</summary>

* [*Array Unique*](#array-unique)
* [*Array Item Count*](#array-item-count)

</details>

## Methods

### Color

#### `HexColor` <=> `RGB`

> Color Converts

```js
const hexToRgb = hex => {
    let _hex = /^#/.test(hex) ? hex.slice(1) : hex
    if(/^(3|6)$/.test(_hex.length)) {
        let h = parseInt(_hex.length === 3
            ? [..._hex].map(i => i + i).join('')
            : _hex, 16)
        return  `rgb(${h >> 16}, ${(h & 0x00ff00) >> 8}, ${h & 0x0000ff})`
    } else {
        console.error('Invalid color value! Parameter rules: range: (0-9 a-f A-F), color code: 3-digit or 6-digit')
    }
}

const rgbToHex = (r, g, b) => {
    const isRange = val => 0 <= val && val <= 255
    return isRange(r) && isRange(g) && isRange(b)
        ? '#' + ((r << 16) + (g << 8) + b).toString(16).padStart(6, '0')
        : console.error('Invalid color value! Parameter rules: value range: (0-255)')
}
```

[[Read More ☞](/part/color.md)] &nbsp;
[[☝︎ Back To TOP]](#table-of-contents)

#### Random HexColor

> Generates a random hexadecimal color code.

```js
const randomHexColor = () => {
    let n = (Math.random()*(1<<24)|0).toString(16)
    return '#' + (n.length !== 6
        ? '0'.repeat(6 - n.length) + n : n)
}
```

[[☝︎ Back To TOP]](#table-of-contents)

### Object

#### Object Has

> Checks if `key` is a direct property of `object`.

```js
const objHas = (obj, key) => obj !== null && Object.prototype.hasOwnProperty.call(obj, key)
```

[[☝︎ Back To TOP]](#table-of-contents)

#### Get Depth Object properties

```js
/**
 * getDeepObj
 * @param {object} obj
 * @param {string} props - object property: using `dot` syntax
 * @example
 * let a = {b: {c: {d: {aa: 3}}}}
 * getDeepObj(a, 'b.c')  // {d: {aa: 3}}
 */
const getDeepObj = (obj, props) => (~props.indexOf('.') ? props.split('.') : [props])
    .reduce((acc, key) => acc && key in acc ? acc[key] : null, obj)
```

[[☝︎ Back To TOP]](#table-of-contents)

### Tools

#### Checks Argument Type

> Checks if the given argument type.

```js
const is = (val, type) => Object.prototype.toString.call(val) === `[object ${type}]`
const isObj = val => is(val, 'Object')
const isArray = val => is(val, 'Array')
const isFunc = val => is(val, 'Function')
const isBool = val => is(val, 'Boolean')
const isRegExp = val => is(val, 'RegExp')
```

[[☝︎ Back To TOP]](#table-of-contents)

#### String To Boolean

> Converts a string to boolean.

```js
const toBool = val => /^true$/i.test(str)
```

[[☝︎ Back To TOP]](#table-of-contents)

#### Set Or Get LocalStorage

> Set/Get localStorage, using methods: [`isObj()`, `isArray()`](#checks-argument-type), [`toBool()`](#string-to-boolean)

```js
// Set localStorage
/**
* @parma {string} key
* @parma {any} val - [number|object|array|string]
*/
const setStorage = (key, val) => localStorage.setItem(key, isObj(val) || isArray(val) ? JSON.stringify(val) : val)

// Get localStorage
const getStorage = key => {
    let _key = localStorage.getItem(key)
    let _ = {
        int: /^-?\d+$/,
        float: /^(-?\d+)(\.\d+)$/,
        bool: /^(true)|(false)$/,
        obj: /^\[?\{|\}\]?$/
    }
    const match = str => str.test(_key)
    if(match(_.int)) return parseInt(_key)
    if(match(_.float)) return parseFloat(_key)
    if(match(_.bool)) return toBool(_key)
    if(match(_.obj)) return JSON.parse(_key)
}
```

[[☝︎ Back To TOP]](#table-of-contents)

#### Set Or Get Or Delete Cookie

> Set/Get/Del Cookie

```js
// Set Cookie
const setCookie = (key, val) => document.cookie = `${key}=${val}`

// Get Cookie
const getCookie = key => {
    return document.cookie.split(';').map(i => {
        let _v = i.trim()
        return new RegExp(`^${key}=`).test(_v)
            ? _v.substr(`${key}=`.length, _v.length) : void 0
    }).join('')
}

// Delete Cookie
const delCookie = key => document.cookie = `${key}=; expires=Thu, 01 Jan 1970 00:00:01 GMT;`
```

[[☝︎ Back To TOP]](#table-of-contents)

#### Generated UUID

```js
// https://stackoverflow.com/questions/105034/create-guid-uuid-in-javascript
const uuid = () => {
    let d = new Date().getTime()
    if(typeof performance !== 'undefined' && typeof performance.now === 'function') {
        d += performance.now()
    }
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, c => {
        let r = (d + Math.random() * 16) % 16 | 0
        d = Math.floor(d / 16)
        return (c === 'x' ? r : (r & 0x3 | 0x8)).toString(16)
    })
}
```

[[☝︎ Back To TOP]](#table-of-contents)

#### orderBy

```js
/**
 * OrderBy
 * @param {Array} arr - Array Of Object
 * @param {String} props - Object properties: using `dot` syntax
 * => {a: b: {c: 1}} // a.b.c => 1
 * @param {String} orders - ['asc' | 'desc'], 'asc' by default
 * @param {Function} fn - callback
 * => syntax: orderBy(arr, props[, orders, fn])
 */
const orderBy = (arr, props, orders, fn) => {
    const getObjVal = obj => (~props.indexOf('.') ? props.split('.') : [props])
        .reduce((acc, key) => acc && key in acc ? acc[key] : null, obj)
    orders = orders === 'desc' ? -1 : 1
    fn = fn === undefined ? cb => cb : fn
    const compare = () => (a, b) => fn(getObjVal(a)) < fn(getObjVal(b)) ? orders * -1 : orders
    return arr.sort(compare())
}
```

[[Read More ☞](/part/orderBy.md)] &nbsp;
[[☝︎ Back To TOP](#table-of-contents)]

### Math

#### Round

> Rounds a number to a specified amount of digits.

```js
const rd = (num, decimals) => Number(`${Math.round(`${num}e${decimals}`)}e-${decimals}`)
```

[[☝︎ Back To TOP](#table-of-contents)]

### Array

#### Array Unique

> Remove duplicate values from an array.

```js
const unique = arr => [...new Set(arr)]

const unique2 = arr => arr.filter((item, index, arr) => arr.indexOf(item) === index)

// let a = [1, 3, 2, 6, 3, 3, 1]
// unique(a) -> [1, 3, 2, 6]
// unique2(a) -> [1, 3, 2, 6]
```

[[☝︎ Back To TOP](#table-of-contents)]

#### Array Item Count

> Count the number of each element in an array.

```js
const arrItemCount = arr => {
    let _arr = new Set()
    Array.from([...new Set(arr)]).map(item => {
        let n = 0
        arr.map(i => i === item ? n++ : void 0)
        _arr.add({[item]: n})
    })
    return [..._arr]
}
// let a = [5,7,1,5,7,5]
// arrItemCount(a) -> [{5: 3}, {7: 2}, {1: 1}]
```

[[☝︎ Back To TOP](#table-of-contents)]

### base64

```js
const b64Encode = str => btoa(encodeURI(str))
const b64Decode = str => decodeURI(atob(str))
```

### reduce()

> arr.reduce(callback[, initialValue])

```js
const flattened = arr => arr.reduce((prev, val) => prev.concat(val), [])

const itemCount = arr => arr.reduce((all, val) => {
    if(val in all) all[val]++
    else all[val] = 1
    return all
}, {})
```

---

### URL

```js
/**
 * strURLToLink
 * Replace the url in the sting with a link
 * @param {String} str
 */
const strURLToLink = str => str.replace(/(https?|ftp)(:\/\/(\w|=|\?|\.|\/|&|-)+)/g, `<a style='word-break: break-all;' href="$1$2">$1$2</a>`)
```

```js
/**
 * URL Parmater Object
 * @return {Object}
 */
const paramURL = () => {
    let o = {}
    decodeURIComponent(location.search.substring(1)).split('&').some(i=> {
        let _i = i.split('=')
        o = _i[0] === '' ? null : Object.assign(o, {[_i[0]]: _i[1]})
    })
    return o === null ? console.log('%cNo parameter object', 'font-weight: bold; color: yellow;') : o
}

/**
 * Query URL
 * @param {String} - key
 * @return {String} - value
 */
const queryURL = key => paramURL()[key]
```

---

### Scroll

```js
const backToTop = () => {
    const s = document.documentElement.scrollTop || document.body.scrollTop
    if(s>0) {
        window.requestAnimationFrame(backToTop)
        window.scrollTo(0, s-s/12)
    }
}
```

---

<!-- ```js
const ab = (a, b) => {
    a^=b,b^=a,a^=b
    return {a,b}
}
``` -->

```js
const throttle = (method, delay) => {
    let last = 0
    return function () {
        let now = Date.now()
        if(now - last > delay) {
            method.apply(this, arguments)
            last = now
        }
    }
}

const debounce = (method, delay) => {
    let timer = null, _ = this
    return function() {
        clearTimeout(timer)
        timer = setTimeout(function() {
            method.call(_)
        }, delay)
    }
}

const unionSet = (...arr) => [...new Set([...arr].reduce((a, b) => [...a].concat([...b])))]

const intersectionSet = (...arr) => [...new Set([...arr].reduce((a, b) => [...a].filter(x => b.includes(x))))]

const differenceABSet = (a, b) => a.concat(b).filter(v => !a.includes(v) || !b.includes(v))
```

---

```js
/**
 * HTML decode
 * @param {String} - &#x5DE7;&#x5408;
 * @example
 * htmlDecode('&#x5DE7;&#x5408;') => 巧合
 */
const htmlDecode = str => str.replace(/&#(x)?(\w+);/g, ($, $1, $2) => String.fromCharCode(parseInt($2, $1 ? 16 : 10)))
```

```js
const tpl = (html, data) => document.querySelector(html).innerHTML
        .replace(/(\{\{)(\w+)(\}\})/g, ($, $1, $2) => data[$2] || '')
```

---

> Hide part of numbers or characters

```js
/**
 * maskPhone
 * @param {Number|String} - phone number
 * @param {Number|String} - hide digits: 4(default) | 6
 * @example
 * maskPhone(12345678910) => "123****8910"
 * maskPhone(12345678910, 6) => "123******10"
 */
const maskPhone = (phone, num = 4) => `${phone}`
    .replace(/(\d{3})(\d+)(\d{2})(\d{2})/, ($, $1, $2, $3, $4) => `${$1}${'*'.repeat(num)}${num == 4 ? $3+$4 : $4}`)

/**
 * maskBankCard
 * @param {Number|String} - bank card number
 * @example
 * maskBankCard(1234323432344019) => "**** **** **** 4019"
 * maskBankCard('1234 3234 3234 4019') => "**** **** **** 4019"
 */
const maskBankCard = card => `${typeof card === 'string'
    ? card.replace(/\s/g, '') : card}`
    .replace(/(\d+)(\d{4})/, ($, $1, $2) => `${'**** '.repeat(3)}${$2}`)
    // .replace(/(.*)(\d{4})/, ($, $1, $2) => `${$1.replace(/.{4}/g, '**** ')}${$2}`)

/**
 * maskEmail
 * @param {String} - email
 * @example
 * maskEmail('alskdl_5456wd@gmail.com') => "a***********d@gmail.com"
 */
const maskEmail = email => email
    .replace(/^(.)(.*)(.@.*)$/, ($, $1, $2, $3) => `${$1}${'*'.repeat($2.length)}${$3}`)

/**
 * maskIDcard
 * @param {Number|String} - ID card
 * @example
 * maskIDcard('12345432345345634x') => "123************34x"
 */
const maskIDcard = card => `${card}`
    .replace(/(\d{3})(\d+)(\w{3})/, ($, $1, $2, $3) => `${$1}${'*'.repeat($2.length)}${$3}`)
```

---

```js
// Bubble Sort
Array.prototype.bubbleSort = function() {
    let tmp = 0,
        lastExchangeIndex = 0,
        len = this.length,
        sortBorder = len - 1

    for(let i=0; i<len; i++) {
        let isSorted = true
        for(let j=0; j<sortBorder; j++) {
            if (this[j] > this[j+1]) {
                tmp = this[j]
                this[j] = this[j+1]
                this[j+1] = tmp
                isSorted = false
                lastExchangeIndex = j
            }
        }
        sortBorder = lastExchangeIndex
        if(isSorted) break
    }

    return this
}

// Quick Sort
Array.prototype.quickSort = function() {
    const len = this.length,
        basic = this[0],
        left = [],
        right = []

    if(len < 2) return this
    for(let i=1; i<len; i++) {
        const iv = this[i]
        iv >= basic && right.push(iv)
        iv < basic && left.push(iv)
    }

    return left.quickSort().concat(basic, right.quickSort())
}
```

---

```js
// Is Odd
const isOdd = num => ~num&1 ? false : true
```