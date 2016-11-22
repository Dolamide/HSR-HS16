# Layering im Browser

## Model & Controller

```js
window.onload=function () {

    // model
    const counter = {
        count: 0,
        countUp: function () {this.count++},
        countDown: function () {this.count--}
    };

    // view-refs
    const countDisplay = document.getElementById("countDisplay");
    const btnUp = document.getElementById("btnUp");
    const btnDown = document.getElementById("btnDown");

    // viewUpdate
    function updateView () {
        countDisplay.innerHTML = counter.count;
    }

    // controller / EventListener
    btnUp.addEventListener("click", function () {counter.countUp(); updateView()});
    btnDown.addEventListener("click", function () {counter.countDown(); updateView()});

    // init
    updateView();
}
```

## View

```html
<body>
<h1>OO-MVC Counter 1</h1>

<p>Count: <span id="countDisplay"></span></p>
<button id="btnUp">Count Up</button>
<button id="btnDown">Count Down</button>

</body>
```
