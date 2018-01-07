# `this`关键字详解

## 含义(Meaning)

> 在构造函数内部需要使用到`this`关键字。那么，`this`关键字到底是什么意思？

`this`指向当前的运行环境：在JavaScript中，所有的函数都是在某个运行环境中运行，`this`就是这个运行环境。对JavaScript语言来说，一切皆对象，运行的环境也是对象，所以可以理解为所有的函数总是在某个对象之中运行，`this`就指向这个对象。*但是JavaScript支持运行环境动态切换，也就是说，this的指向是动态的，没有办法可以事先确定到底指向哪个对象*

> 例：有一个函数`xOfVal`，同时充当`a`对象和`b`对象的`say`方法，用于打印当前运行环境中`x`变量的值。JavaScript允许函数`xOfVal`的运行环境动态切换，即一会属于`a`对象，一会属于`b`对象，这就需要靠`this`关键字来办到

```js
function xOfVal() {console.log(this.x)}

var a = {x: 5}
var b = {x: 7}
a.say = xOfVal
b.say = xOfVal

a.say() // 5
b.say() // 7
```

当`xOfVal`属于对象`a`时，`this`指向`a`；当`xOfVal`属于对象`b`时， `this`指向`b`，*因此打印出不同的值*。由于`this`的指向是可变的，所以可以手动切换运行环境，以达到某种特定的目的。

*结论*：*__如果一个函数在全局环境中运行，`this`就是指向顶层对象(浏览器中为`window`对象)；如果一个函数作为某个对象的方法运行，`this`就是指向那个对象。 可以近似认为，`this`事所有函数运行时的一个隐藏参数，决定了函数的运行环境。__*

## 使用场合(Using The Occasion)

### 全局环境(Global Context)

> 在全局环境中使用`this`，它指的时顶层对象window。

```js
console.log(this === window) // true

function fn() {
    console.log(this === window)
}

fn() // true
```

*结论*： *__`this`不论是不是在函数内部，只要是在全局环境下运行，`this`就是指向全局对象`window`__*

### 构造函数(Constructor)

> 在构造函数中使用`this`，它指的是实例对象

```js
// 构造函数A
var A = function(x) {
    // this指向实例对象
    // 所以在构造函数内部定义`this.x`，就相当于定义实例对象有一个`x`属性
    this.x = x
}

// `say`方法可以返回这个`x`属性
A.prototype.say = function() {
    return this.x
}

var a = new A(3)

a.x // 3
a.say() // 3
```

### 对象方法(Object Method)

* 当`a`对象的方法被赋予`b`对象，该方法就变成了普通函数。其中的`this`就从指向`a`对象变成指向`b`对象。这就是`this`取决于运行时所在的对象的含义。*需要特别小心。如果将某个对象的方法赋值给另一个对象，会改变`this`的指向。*

```js
var a = {
    // `prop`是`a`对象的属性
    prop: 'hello',
    // `f`是`a`对象的方法
    f: function() {
        return this.prop
    }
}

a.f() // hello

var b = new Object()
b.prop = 'hello, lencx'
// `f`是`a`对象的方法
b.f = a.f
// 如果在`b`对象上调用这个方法。`f`方法中的`this`就会指向`b`
// 说明JavaScript函数的运行环境完全是动态绑定的，可以在运行时切换。
b.f() // hello, lencx
```

* 如果不想改变`this`的指向，可以将`b.f`改写为

```js
b.f = function() {
    // `f`方法是在`a`对象下运行，所以`this`指向`a`
    return a.f()
}
b.f() // hello
```

* 有时，某个方法位于多层对象的内部，这时如果为了简化书写，把该方法赋值给一个变量，往往会得到意想不到的结果。

```js
var a = {
    b: {
        prop: 'hello, lencx',
        say: function() {
            console.log(this.prop)
        }
    }
}
// `say`属于多层对象内部的一个方法。为求简写，将其赋值给`hello`变量
var hello = a.b.say
// 调用时，`this`指向全局对象(window)
hello() // undefined

// 为了避免这个问题，可以将`say`方法所在的对象赋值给`hello2`
var hello2 = a.b
// 调用时，`this`指向不变，即指向对象`b`
hello2.say()
```

### 箭头函数(Arrow functions)

```js
var foo = (() => this)
// 在全局环境中调用`foo`，`this`指向`window`
console.log(foo() === window) // true

var a = {}
// 作为`a`对象的`fn`方法调用
a.fn = foo
console.log(a.fn() === window) // true

// 使用`call`
console.log(foo.call(a) === window) // true

// 使用`bind`
foo = foo.bind(a)
console.log(foo() === window) // true
```

*结论*：*__无论使用何种办法，`foo`方法的`this`指向都是创建时的指向(window)。这个结论同样适用于在其他函数内部创建的箭头函数。`this`指向创建它的对象。__*

例：

```js
var obj = {foo: function() {
    var x = (() => this)
    // var x = function() {
    //     return this
    // }
    return x
}}

var fn = obj.foo()
console.log(fn() === obj) // true

// 但是请注意，如果将`foo`所在的对象赋值给一个变量`fn2`，而不是调用`foo`方法
var fn2 = obj.foo
// 然后调用该方法，则`this`指向`window`，因为它遵循所在的对象运行环境
console.log(fn2()() === window) // true
```

### 对象定义新属性方法(Getter Or Setter)

```js
function sum() {
    return this.x + this.y + this.z
}

var numObj = {
    x: 3,
    y: 5,
    z: 7,
    get average() {
        return (this.x + this.y + this.z) / 3
    }
}

Object.defineProperty(numObj, 'sum', {
    get: sum,
    enumerable: true,
    configurable: true
})

console.log(numObj.average, numObj.sum) // 5 15
```

### Node.js

在node.js，`this`分成两种情况。在全局环境中，`this`指向全局对象`global`；在模块环境中，`this`指向`module.exports`

```js
// 全局环境中
this === global // true

// 模块环境中
this === module.exports // true
```

## 使用注意事项(Note)

### 避免多层`this`

```js
var o = {
    f1: function() {
        console.log(this) // f1
        var f2 = function() {
            console.log(this) // window
        }()
    }
}
o.f1()

// 解决办法:
var o2 = {
    f1: function() {
        console.log(this) // f1
        // 使用`that`对`this`进行固定
        var that = this
        var f2 = function() {
            // 使用`that`代替原来的`this`
            console.log(that) // f1
        }()
    }
}
o2.f1()
```

### 避免数组处理方法中的`this`

数组的`map`, `reduce`, `some`, `filter`, `forEach`等方法，允许提供一个函数作为参数。这个函数内部不应该使用`this`。

```js
var o = {
    a: 'hello',
    b: ['lencx', 'a1', 'a2'],
    fn: function() {
        this.b.map(function(item) {
            console.log(`${this.a}, ${item}`)
        })
    }
}
// undefined, lencx
// undefined, a1
// undefined, a2
o.fn()

// ------------------------------------------

// 解决办法一：
// 使用中间变量
var o2 = {
    a: 'hello',
    b: ['lencx', 'a1', 'a2'],
    fn: function() {
        var that = this
        this.b.map(function(item) {
            console.log(`${that.a}, ${item}`)
        })
    }
}
// hello, lencx
// hello, a1
// hello, a2
o2.f()

// ------------------------------------------

// 解决办法二：
// 将`this`当作`map`方法的第二个参数，固定它的运行环境
var o3 = {
    a: 'hello',
    b: ['lencx', 'a1', 'a2'],
    fn: function() {
        this.b.map(function(item) {
            console.log(`${this.a}, ${item}`)
        }, this)
    }
}

// hello, lencx
// hello, a1
// hello, a2
o3.fn()
```

### 避免回调函数中的`this`

> 回调函数中的`this`往往会改变指向，最好避免使用

```js
var o = new Object()
o.f = function() {
    console.log(this === o)
}
o.f() // true

// `this`不再指向`o`对象，而是指向按钮的DOM对象
// 因为`f`方法是在按钮对象的环境中被调用的
document.querySelector('#btn').addEventListener('click', o.f)
```

## 固定`this`的方法(Fixed this)

`this`的动态切换，为JavaScript创造了巨大的灵活性，但也使编程变得困难和模糊。有时需要把`this`固定下来，避免出现意想不到的情况。JavaScript提供了`call`, `apply`, `bind`三个方法，来切换/固定`this`的指向。

### `call`方法

> Syntax: function.call(thisArg, arg1, arg2, ...)

第一个参数`thisArg`就是`this`所要指向的对象，之后的参数`arg1, arg2, ...`则是函数调用时所需的参数。

```js
// 例1:
var o = {}
var f = function () {
    return this
}
f() === window // true
f.call(o) === o // true

// 例2:
var num = 111
var num2 = {num: 222}
function sayNum() {
    console.log(this.num)
}
sayNum.call() // 111
sayNum.call(window) // 111
sayNum.call(num2) // 222
```

`call`的应用：调用对象的原生方法

```js
var obj = {}
obj.hasOwnProperty('map') // false

obj.hasOwnProperty = function() {
    return true
}
obj.hasOwnProperty('map') // true
Object.prototype.hasOwnProperty.call(obj, 'map') // false
```

`hasOwnProperty`是`obj`对象继承的方法，如果这个方法一旦被覆盖，就得不到正确的结果。`call`方法则可以解决这个问题。它将`hasOwnProperty`方法的原始定义放到`obj`对象上执行，这样无论`obj`上有没有同名方法，都不会影响其结果。

### `apply`方法

> Syntax: func.apply(thisArg, [argsArray])

`apply`方法与`call`类似，也是改变`this`指向，然后再调用该函数。唯一区别是，它接收一个数组作为函数执行时的参数。

```js
function sum(x, y) {
    console.log(x + y)
}
sum.call(null, 2, 4) // 6
sum.apply(null, [2, 4]) // 6

// --------------------------------------------------

// 对字符串中的单个字符进行重复操作
//Uncaught TypeError: "abcd".map is not a function
'abcd'.map(i => console.log(i))
// aabbccdd
Array.prototype.map.call('abcd', i => i+i).join('')
```

#### 应用(Use)

* 找出数组中最大/最小的元素

```js
var a = [4, 7, 3, 9, 11, 1]
Math.max.apply(null, a) // 11
Math.min.apply(null, a) // 1
```

* 将数组的空元素变为`undefined`(数组遍历会跳过空元素，但是不会跳过undefined)

```js
Array.apply(null, [1, 2, , 3]) // [1, 2, undefined, 3]
```

* 转换类似数组的对象(被处理的对象必须有`length`属性，以及相对应的数字键)

```js
// 例1:
var o = {
    0: 1,
    1: 3,
    length: 2
}
Array.prototype.slice.apply(o) // [1, 3]

// 例2:
var o2 = {
    0: 1,
    1: 3
}
Array.prototype.slice.apply(o2) // []

// 例3:
var o3 = {
    0: 1,
    1: 3,
    length: 4
}
Array.prototype.slice.apply(o3) // [1, 3, empty × 2]

// 例4:
var o4 = {
    1: 1,
    a: 3,
    length: 2
}
Array.prototype.slice.apply(o4) // [empty, 1]
```

* 绑定回调函数的对象(之前[绑定按钮点击事件](#避免回调函数中的this)的例子)

```js
var o = new Object()
o.f = function() {
    console.log(this === o)
}

// `apply`或者`call`方法不仅绑定函数执行时所在的对象，还会立即执行函数。因此要把绑定语句写在一个函数体内。
var foo = function() {
    // o.f.call(o)
    o.f.apply(o)
}

// true
document.querySelector('#btn').addEventListener('click', foo)
```

### `bind`方法

> Syntax: fun.bind(thisArg[, arg1[, arg2[, ...]]])

* `bind`方法用于将函数体内的`this`绑定到某个对象，然后返回一个新函数。

```js
var o = new Object()
o.name = 'lencx'
o.say = function() {
    console.log(this.name)
}

o.say() // lencx

var o2 = new Object()
o2.name = 'len'
o2.say = o.say
o2.say() // len

o2.say = o.say.bind(o)
o2.say() // lencx
```

* `bind`除了可以绑定`this`以外，还可以绑定原函数的参数

```js
var sum = function(x, y) {
    return x * this.a + y * this.b
}

var nums = {
    a: 3,
    b: 4
}

var newSum = sum.bind(nums, 3)
newSum(3)
```

#### 注意事项(Note)

* 每次绑定都返回一个新函数

```js
// 点击事件绑定`bind`方法生成的一个匿名函数。会导致无法取消绑定。
element.addEventListener('click', o.say.bind(o))
// 因此下面的代码无效
element.removeEventListener('click', o.say.bind(o))

// 正确解法：
var _say = o.say.bind(o)
element.addEventListener('click', _say)
element.removeEventListener('click', _say)

```

* `bind`方法的兼容(Polyfill)

```js
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
if (!Function.prototype.bind) {
  Function.prototype.bind = function(oThis) {
    if (typeof this !== 'function') {
      // closest thing possible to the ECMAScript 5
      // internal IsCallable function
      throw new TypeError('Function.prototype.bind - what is trying to be bound is not callable');
    }

    var aArgs   = Array.prototype.slice.call(arguments, 1),
        fToBind = this,
        fNOP    = function() {},
        fBound  = function() {
          return fToBind.apply(this instanceof fNOP
                 ? this
                 : oThis,
                 aArgs.concat(Array.prototype.slice.call(arguments)));
        };

    if (this.prototype) {
      // Function.prototype doesn't have a prototype property
      fNOP.prototype = this.prototype;
    }
    fBound.prototype = new fNOP();

    return fBound;
  };
}
```

* 结合`call`方法使用

```js
[1, 2, 3].slice(0, 1) // [1]

// 等同
Array.prototype.slice.call([1, 2, 3], 0, 1) // [1]

// `call`方法实质是调用`Function.prototype.call`方法
var slice = Function.prototype.call.bind(Array.prototype.slice)
slice([1, 2, 3], 0, 1) // [1]
```

- 利用`bind`方法，将`[1, 2, 3].slice(0, 1)`变成了`slice([1, 2, 3], 0, 1)`的形式。这种改变也可以应用到其他数组方法。

```js
var pop = Function.prototype.call.bind(Array.prototype.pop)
var push = Function.prototype.call.bind(Array.prototype.push)
var shift = Function.prototype.call.bind(Array.prototype.shift)
var map = Function.prototype.call.bind(Array.prototype.map)
// ...

var a = [1, 2, 3]
pop(a) // [1, 2]
push(a, 5) // [1, 2, 5]
shift(a) // [2, 5]
map(a, i => i+1) // [3, 6]
```

* 将`Function.prototype.call`绑定到`Function.prototype.bind`对象，`bind`的调用形式也可以被改写

```js
function foo() {
    console.log(this.name)
}

var o = {name: 'lencx'}

var bind = Function.prototype.call.bind(Function.prototype.bind)

bind(foo, o)() // lencx
```

参考：
* MDN Web Docs: 
[this](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/this),
[defineProperty](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/defineProperty),
[call](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/call),
[bind](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind),
[apply](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/apply)