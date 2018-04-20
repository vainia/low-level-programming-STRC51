class ButtonArray{
  constructor(divid){
    this.divid = document.getElementById(divid);
    this.buttonArray = ButtonArray.makeArray();
    this.buffor = [];
    this.testArray = ButtonArray.make2dArray(this.buttonArray);
    console.log(this.testArray);
  }
  static makeArray(){
    var array = [];
    var iter = 6;
    for(var y = 1; y < 5; y += 1){
      for(var x = 1; x < 5; x += 1){
        array.push(`Sw${iter++}`);
      }
    }
    //Dirty work around. "It will make trouble later" - Me. 2015-06-17
    array[0] = "Sw06";
    array[1] = "Sw07";
    array[2] = "Sw08";
    array[3] = "Sw09";
    return array;
  }

  static makeElement(elem){
    var t = document.createElement("button");
    t.setAttribute("id",elem);
    t.setAttribute("class","key");
    t.onclick =  function(e){
      if(this.className == "key"){
        this.className = "pressed";
      } else {
        this.className = "key";
      }
    };
    t.innerHTML = elem;
    return t;
  }

  static makeRow(arr,offset){
    var t = [];
    for(var y = offset; y < offset+4; y+=1){
      t.push(ButtonArray.makeElement(arr[y]))
    }
    return t;
  }

  static make2dArray(arr){
    var t = [];
    for(var x = 0; x < 4; x += 1 ){
      t.push(ButtonArray.makeRow(arr,x*4));
    }
    return t
  }




  getTestArray(){
    return this.testArray;
  }
  makeButtons(){
    this.testArray.forEach(bt => {
      bt.forEach(elem => {

        this.divid.appendChild(elem);
      });
    });
  }

  checkRow(row){

    for(var i = 0; i < 4; i ++){
      var elclass = this.testArray[i][row].className;
      if(elclass === "key"){
        continue;
      }else{
        
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
}
