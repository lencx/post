# OrderBy

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

/******
* test data
*/
let a = [
    {date: '2017.2.22', thing: 'six'},
    {date: '2017/1/14', thing: 'three'},
    {date: '2017/01/23', thing: 'four'},
    {date: '2017 1 1', thing: 'one'},
    {date: '2017-1-9', thing: 'two'},
    {date: '2.21 2017',thing: 'five'}
]
let b = [
    {part: {title: 'two', content: 'content 1'}, id: 'dskjk238128430412'},
    {part: {title: '123', content: 'content 2'}, id: 'asdadrerkj323ewes'},
    {part: {title: 'abc', content: 'content 3'}, id: 'opopklkqwlqoeo234'},
    {part: {title: 'one', content: 'content 4'}, id: 'ai324389585ik12md'},
    {part: {title: 'four', content: 'content 5'}, id: 'tr432cdsdsdcnnmsd'},
]
orderBy(a, 'date', 'asc', date => new Date(date))
orderBy(a, 'date', 'desc', date => new Date(date))
orderBy(a, 'thing')
orderBy(a, 'thing', 'desc')

orderBy(b, 'id')
orderBy(b, 'part.title', 'desc')
```

![data](/img/js/orderby-a.png)
![data](/img/js/orderby-b.png)

[[↻ Back To Home](/README.md)] &nbsp;
[[☝︎ Back To TOP](#orderby)]