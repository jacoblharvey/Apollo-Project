

// robot version 6  9/30/20


include <pinSocket.scad>


module servoArm(){
  cylinder(d=7,h=4,$fn=32);
  translate([-5.5/2,0,0])cube([5.5,17,4]); 
}




module servo(armRot){
  translate([-12.3/2,-12.3/2,0]){  
    cube([22.5,12.3,22.5]);
    difference(){
      translate([-5,0,16])cube([32.5,12.3,2.3]);
      translate([-3,12.3/2,0])cylinder(d=2.5,h=40,$fn=32);
      translate([25.5,12.3/2,0])cylinder(d=2.5,h=40,$fn=32);
    }
    translate([22.5/2,12.3/2,0])cylinder(d=6,h=27.5,$fn=32);
    translate([12.3/2,12.3/2,0])cylinder(d=12.3,h=27.5,$fn=32);
    translate([12.3/2,12.3/2,0])cylinder(d=5,h=27.5+3.5,$fn=32);
  }

  translate([0,0,28])rotate([0,0,armRot])servoArm();


}

// servo();



module ring(sz){
  difference(){
    cylinder(d=sz,h=5);
    translate([0,0,-1])cylinder(d=sz-10,h=10);
  }
}

module oneSnap(){
  servoMPT = 2.5;   // servo mounting plate thickness
  mpt = servoMPT + 0.4;  // servo slot
  springT = 1.6; 

  difference(){
    translate([0,0,0])cube([4,16,18]);
    translate([-1,3.75,4]) cube([6,mpt,12.5]);
    translate([-1,4.75,2]) cube([6,mpt-1,18]);

    translate([-1,3.75+mpt+springT,2]) cube([6,4.0,20]);
  }    
  translate([0,6.7,0])cube([4,2,5.]);  
}


module snapJoint(servoRot,armRot){
  ys = 5;
  zs = 7.7+1.5;
  translate([11.75,0,1.99])oneSnap();
  translate([-15.75,0,1.99])oneSnap();
  translate([0,3+ys,zs-7.7])cube([31.5,16,3],center=true);

  if(servoRot == 1){
    translate([-5,22.2,12.2])rotate([90,0,0])color("blue")servo(armRot);
  } else {
    translate([5,22.2,12.2])rotate([90,180,0])color("red")servo(armRot);
  }
}



// snapJoint();
module supportFrame(){ //This is for the top support for the bboard
    
  translate([0,125,30])cube([85,5,5]);
    
    
    }

module frame(){ // 80x100
  cube([5,125,5]);
  cube([85,5,5]);
  translate([80,0,0])cube([5,125,5]);
  translate([0,125,0])cube([85,5,5]);
  translate([0,20,0])rotate([0,0,-90])snapJoint(1,120);
  translate([85,20,0])rotate([0,0,90])snapJoint(0,120);

  translate([15,36,25])cube([55,85,10]);   // breadboard

    translate([0,100,0])cube([5,5,20]);  // post
    translate([80,100,0])cube([5,5,20]);  // post
    translate([0,40,0])cube([5,5,20]);
    translate([80,40,0])cube([5,5,20]);

}


module leg(){
  difference(){
    translate([-5,-5,-2])cube([10,25,5]);
    servoArm();
  }   
  translate([-2.5,20,-2])cube([5,30,5]);

}

// leg();

module rail(){
   difference(){
    translate([0,0,0])rotate([0,90,0])cylinder(d=70,h=5,$fn=64);
    translate([-2,0,0])rotate([0,90,0])cylinder(d=60,h=10,$fn=64);
    translate([-5,-35,0])cube([25,75,40]);
   }
    }

module railTwo(){
   difference(){
    translate([0,0,0])rotate([0,90,0])cylinder(d=70,h=5,$fn=64);
    translate([-2,0,0])rotate([0,90,0])cylinder(d=60,h=10,$fn=64);
    translate([-5,-35,0])cube([25,75,40]);
   }
    
}

module wheelLeft(){
    translate([0,0,13])rotate([0,90,0])cylinder(d=100,h=5,$fn=64);
    
    }



wheelLeft();
//print the rails separately
//translate([0,95,0])rail();
//translate([80,95,0])railTwo();
//frame();

//print support frame separately
//supportFrame();


//difference(){
//  ring(60);
//  translate([0,0,-1])cube([100,100,100]);
//}

// translate([20,0,0])ring(50);
// translate([20,20,0])ring(100);


// servo();

// hindge(5,0.6,50,0);

// socketX(10);
 // translate([-34.9,0,0])cube([50,5,10],center=true);

 // ballS(10);
// translate([25,0,0])cube([50,5,10],center=true);


