# 组件库

## 组件和抽象

> 组件是一种编程抽象，目的是复用
>> `通用型组件库`  `业务型组件库`

### 抽象

* DRY 原则：Don't repeat yourself 《程序员修炼之道》<sub>从小工到专家</sub>
* 三次原则：Rule of three 《重构》<sub>改善已有代码设计</sub>

### 组件设计

> 高内聚，低耦合 《敏捷软件开发》<sub>原则，模式与实践</sub>
* 内聚性 - 粒度
* 耦合性 - 稳定

### 粒度

* CRP 共同复用原则：The Common Reuse Principle, CRP
  * SRP 单一职责原则<sub>(**尽量做到**)</sub>
* CCP 公用封闭原则：The Common Closure Principle <sub>(一个组件不该包含多个引起它变化的原因)</sub>

#### 一个组件应不应该引用另一个组件？

* 依赖的弊端
  * 耦合：`高维护成本` `不稳定性`
* 代码可维护性大于复用性

### 稳定

* SDP 稳定依赖原则：The Stable-Dependencies Principle
* SAP 稳定抽象原则：The Stable-Abstractions Principle

#### 父子组件如何依赖？

* loC 好莱坞原则：Hollywood Principle
  > Don't call us, we'll call you \
  > 子组件的初始化和调用由父组件容器负责
* CoC 约定大于配置原则：Convention over Configuration

### 设计禁区

* 越界操作
* 副作用
* 侵入性
* 环形依赖
* 属性繁多

### 设计规范先行

* 统一视觉样式
  * 色彩
  * 布局
  * 字体
  * 图标
* 统一交互动效
  * 时长，缓动
  * 移动路径
  * 形变，编排

#### Material Design

* 光效、表面质感、运动感
* 鲜明、形象、有意义
* 有意义的动画效果

### 样式分离

> `多种主题` `主题定制工具` `交互动画扩展`

* 需求
  * 主题定制
  * 样式差异化

### 辅助平台/工具

* 文档
* 脚手架
* 示例
* 迭代

## 组件库工程化最佳实践

### 组件管理方案

* 需求：
  * 多组件
  * 多人参与
  * 社区参与
  * 私密性

### [lerna(多包管理工具)](https://lernajs.io/)

* 优点：
  * 一键安装依赖
  * 自动更新依赖
  * 独立版本管理
  * 非NPM包

### 国际化(i18n)

* zh-CN 简体中文
* zh-TW 繁体中文
* en 英语
* ...

### 测试方案

* Karma 驱动
* Mocha 测试框架
* Chai 断言库
* Mock 模拟API
* Istanbul 覆盖率

### Jest

> 一站式测试方案

* DOM API
* 断言库
* Mock库
* 快照
* 覆盖率

### 组件库构建方案

### ES模块输出规范

> [Rollup](https://rollupjs.org): Tree-shaking

* `umd`: commonjs & azmd
* `cjs`
* `es`

```js
// rollup.config.js
export default {
  entry: 'src/main.js',
  output: [{
    file: 'dist/bundle.umd.js',
    name: 'bundle',
    format: 'umd',
  }, {
    file: 'dist/bundle.cjs.js',
    format: 'cjs',
  }, {
    file: 'dist/bundle.es.js',
    format: 'es',
  }]
}
```

### Github集成

* Travis CI 持续集成
  * [travis-ci.org](https://travis-ci.org/) 开通服务
  * [coveralls.io](https://coveralls.io/) 开通服务
  * 配置 .travis.yml

### 文档方案

* [docsify](https://docsify.js.org)
  * 多语言
  * git pages
  * 全文检索
  * 插件扩展

### 翻译方案

* [crowdin](https://crowdin.com/)
  * 逐句翻译
  * 翻译推荐
  * 进度管理
  * 审核机制

## 组件库工具新探索

### 实时案例展示

* [codepen](https://codepen.io/)
* [jsbin](https://jsbin.com/)
* ...

### 可视化配置

* 组件配置文件：通过配置文件，生成对应的组件
  ![流程图](/static/img/component/1.png)

### 组件配置自动生成

### 文档自动生成

### 主题配置工具