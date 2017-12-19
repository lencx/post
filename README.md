# JavaScript Tricks

## Table of Contents

* [`HexToRgb`](#hextorgb)
* [`Checks Argument Type`](#checksargumenttype)
    > `isObj()`, `isArray()`, `isFunc()`, `isBool()`, `isRegExp()`
* [`StrToBool`](#strtobool)
* [`Set/Get localStorage`](#setorgetlocalstorage)
    > `setStorage()`, `getStorage()`
* [`Set/Get Cookie`](#setorgetcookie)
    > `setCookie()`, `getCookie()`

## Methods

### HexToRGB

> Converts a hex color to a `rgb()` string.

```js
const hexToRgb = hex => {
    let len = hex.length
    if(/^#[A-Fa-f0-9]{3}|[A-Fa-f0-9]{6}$/.test(hex) && (len === 4 || len === 7)) {
        let h = parseInt(
            hex.length === 4
                ? Array.prototype.map.call(hex.slice(1), i => i+i).join('')
                : hex.slice(1)
        , 16)
        return `rgb(${h >> 16}, ${(h & 0x00ff00) >> 8}, ${h & 0x0000ff})`
    } else {
        console.error('Invalid color value! Parameter rules: Start with `#`, length `3` or `6`, range `0-9`, `a-f`, `A-F`')
    }
}
// hexToRgb('#acd') => "rgb(170, 204, 221)"
// hexToRgb('#AAccdd') => "rgb(170, 204, 221)"
// hexToRgb('acd') => 'Invalid color value! ...'
```

![hexToRgb console error](./img/js/hextorgb.png)

[☝︎ Back To TOP](#table-of-contents)

### ChecksArgumentType

> Checks if the given argument type.

```js
const is = type => Object.prototype.toString.call(type)
const isObj = val => is(val) === '[object Object]'
const isArray = val => is(val) === '[object Array]'
const isFunc = val => is(val) === '[object Function]'
const isBool = val => is(val) === '[object Boolean]'
const isRegExp = val => is(val) === '[object RegExp]'
```

[☝︎ Back To TOP](#table-of-contents)

### StrToBool

> Converts a string to boolean.

```js
const toBool = val => /^true$/i.test(str)
```

[☝︎ Back To TOP](#table-of-contents)

### SetOrGetLocalStorage

> Set/Get localStorage, using methods: [`isObj()`, `isArray()`](#checksargumenttype), [`toBool()`](#strtobool)

```js
// Set localStorage
/**
* @parma {String} key
* @parma {Any} val - [Number | Object | Array]
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

[☝︎ Back To TOP](#table-of-contents)

### SetOrGetCookie

> Set/Get Cookie

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
```

[☝︎ Back To TOP](#table-of-contents)