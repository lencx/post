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
* [*Set/Get Cookie*](#set-or-get-cookie)
    > `setCookie()`, `getCookie()`
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

#### Set Or Get Cookie

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
 * orderBy
 * @param {array} arr - array object
 * @param {string} prop - object property: property - using `dot` syntax
 * @param {string} orders - ascending(`asc`) or descending(`desc`): 'asc' by default
 */
const orderBy = (arr, props, orders) => {
    const deepObj = obj => (~props.indexOf('.') ? props.split('.') : [props])
        .reduce((acc, key) => acc && key in acc ? acc[key] : null, obj)
    const compare = (props, orders) => {
        orders = orders === 'desc' ? -1 : 1
        return (a, b) => deepObj(a) < deepObj(b) ? orders * -1 : orders * 1
    }
    return arr.sort(compare(props, orders))
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

<!-- ```js
const ab = (a, b) => {
    a^=b,b^=a,a^=b
    return {a,b}
}
``` -->