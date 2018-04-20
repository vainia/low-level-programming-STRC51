//run.js

var test = new ButtonArray("keyboard");
test.makeButtons();
var interval;
function run(speed=1000){
  var u15 = document.getElementById("u15");
  var u12 = document.getElementById("u12");
  var i = 0;
  var q = function(i,r=false){
    var r = [1,1,1,1];
    r[i] = 0;
    if(r===true){
      r.reverse();
    }
    var ret = r.join('');
    return ret;
  };
  interval = setInterval(function(){
    if(i == 4){
      i = 0;
    }
    u15.innerHTML = `U15 = ${q(i)}`;
    var el = test.checkRow(i);
    if(!isNaN(el)){
      console.log(el);
      var str = `U12 = ${q(el)}`;
      u12.innerHTML =   str;
    }else{
      console.log("no click detected "  );
    };
    i++;
  },speed);


}
function stop(interval){
  window.clearInterval(interval);
}


document.getElementById("start").addEventListener("click",function(e){

  var speed = parseInt(document.getElementById("speed").value);
  if(speed === NaN){
    speed = 1000;
  }
  if(this.innerHTML == "Start"){
    run(speed);
    this.innerHTML = "Stop";
  }else{
    stop(interval);
    this.innerHTML = "Start";
  }
  console.log(interval);
});
