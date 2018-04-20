"use strict";

var _createClass = (function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; })();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var ButtonArray = (function () {
  function ButtonArray(divid) {
    _classCallCheck(this, ButtonArray);

    this.divid = document.getElementById(divid);
    this.buttonArray = ButtonArray.makeArray();
    this.buffor = [];
    this.testArray = ButtonArray.make2dArray(this.buttonArray);
    console.log(this.testArray);
  }

  _createClass(ButtonArray, [{
    key: "getTestArray",
    value: function getTestArray() {
      return this.testArray;
    }
  }, {
    key: "makeButtons",
    value: function makeButtons() {
      var _this = this;

      this.testArray.forEach(function (bt) {
        bt.forEach(function (elem) {

          _this.divid.appendChild(elem);
        });
      });
    }
  }, {
    key: "checkRow",
    value: function checkRow(row) {

      for (var i = 0; i < 4; i++) {
        var elclass = this.testArray[i][row].className;
        if (elclass === "key") {
          continue;
        } else {

          return i;
        }
        return false;
      }
    }

    /*
      CheckAllRows(){
        unsafe
          changeing u15 here...
    
        var q = function(i){
          var r = [1,1,1,1];
          r[i] = 0;
          r.join("");
          return r;
        };
        var u15= document.getElementById("u15");
        var rows = [1,1,1,1];
    
        for(var i = 0; i < 4; i ++ ){
    
          var bool = this.checkRow(i);
    
          u15.innerHTML = `U15 = ${q(i)}`
          if(bool){
            rows[i]=0;
          } else {
            rows[i]=1;
          }
    
        }
        return rows;
      }
      */

  }], [{
    key: "makeArray",
    value: function makeArray() {
      var array = [];
      var iter = 6;
      for (var y = 1; y < 5; y += 1) {
        for (var x = 1; x < 5; x += 1) {
          array.push("Sw" + iter++);
        }
      }
      //Dirty work around. "It will make trouble later" - Me. 2015-06-17
      array[0] = "Sw06";
      array[1] = "Sw07";
      array[2] = "Sw08";
      array[3] = "Sw09";
      return array;
    }
  }, {
    key: "makeElement",
    value: function makeElement(elem) {
      var t = document.createElement("button");
      t.setAttribute("id", elem);
      t.setAttribute("class", "key");
      t.onclick = function (e) {
        if (this.className == "key") {
          this.className = "pressed";
        } else {
          this.className = "key";
        }
      };
      t.innerHTML = elem;
      return t;
    }
  }, {
    key: "makeRow",
    value: function makeRow(arr, offset) {
      var t = [];
      for (var y = offset; y < offset + 4; y += 1) {
        t.push(ButtonArray.makeElement(arr[y]));
      }
      return t;
    }
  }, {
    key: "make2dArray",
    value: function make2dArray(arr) {
      var t = [];
      for (var x = 0; x < 4; x += 1) {
        t.push(ButtonArray.makeRow(arr, x * 4));
      }
      return t;
    }
  }]);

  return ButtonArray;
})();
//run.js

"use strict";

var test = new ButtonArray("keyboard");
test.makeButtons();
var interval;
function run() {
  var speed = arguments[0] === undefined ? 1000 : arguments[0];

  var u15 = document.getElementById("u15");
  var u12 = document.getElementById("u12");
  var i = 0;
  var q = function q(i) {
    var r = arguments[1] === undefined ? false : arguments[1];

    var r = [1, 1, 1, 1];
    r[i] = 0;
    if (r === true) {
      r.reverse();
    }
    var ret = r.join("");
    return ret;
  };
  interval = setInterval(function () {
    if (i == 4) {
      i = 0;
    }
    u15.innerHTML = "U15 = " + q(i);
    var el = test.checkRow(i);
    if (!isNaN(el)) {
      console.log(el);
      var str = "U12 = " + q(el, true);
      u12.innerHTML = str;
    } else {
      console.log("no click detected ");
    };
    i++;
  }, speed);
}
function stop(interval) {
  window.clearInterval(interval);
}

document.getElementById("start").addEventListener("click", function (e) {

  var speed = parseInt(document.getElementById("speed").value);
  if (speed === NaN) {
    speed = 1000;
  }
  if (this.innerHTML == "Start") {
    run(speed);
    this.innerHTML = "Stop";
  } else {
    stop(interval);
    this.innerHTML = "Start";
  }
  console.log(interval);
});
