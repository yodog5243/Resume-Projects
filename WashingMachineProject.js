class FSA {
  constructor() {
    class Memento {
      constructor(state) {
        this.getState = () => state;
        //storeState(s: string): void
        this.storeState = (s) => { this.getState = () => s; }
      }
    } 
    class State {
      constructor(name) {
        //addTransition(e: string,s: State): void
        this.addTransition = (e,s) => {
          let object = {};
          let transitionArray = this.getTransitions(); //create an array from the transitions using the get transitions
          setPropertyValue(object,e,s); //set the value of state for the object
          transitionArray.push(object); //put that newly created state into the transition array
          this.getTransitions = () => transitionArray;
        }
        //nextState(e: string): State
        this.nextState = (e) => {
          let nextStates = this.nextStates(e); //call nextstates on the object with event as input to get the full list of states connected on that event
          if (nextStates.length === 0) { return undefined;} //check to make sure there are states connected by that event
          return nextStateMath(nextStates); //call nextStateMath which will randomly select a value from an array, input all the state options in
        }
        //nextStates(e: string): State[]
        this.nextStates = (e) => {
          let transitions = this.getTransitions(); 
          let lessTransitions = transitions.filter(x => Object.keys(x)[0] === e); //filter the transitions array by which ones match with the event
          let transitionsPropertys = lessTransitions.map(x => getPropertyValue(x,e)); //map the lessTransitions array to transitionsPropertys by each objects corresponding states based on inputed events
          return transitionsPropertys;
        }     
        //setName(name: string): () => string
        this.setName = (newName) => { this.getname = () => newName; }
        this.getTransitions = () => []; //returns an array associated with object this
        this.getName = () => name; //getname returns the name associated with object this
      }
    }
    //method to randomly select from an array
    let nextStateMath = (x) => {
      return x[Math.floor(Math.random() * x.length)];
    }
    //lib220.getProperty moved to an accesible function
    let getPropertyValue = (variable,event) => {
      return lib220.getProperty(variable,event).value;
    }
    //lib220.setProperty moved to an accesible function
    let setPropertyValue = (obj,event,state) => {
      return lib220.setProperty(obj,event,state);
    }
    //another random value decider I messed with
    let randomArrVal = (length,arr) => {
      let randInt = Math.floor(Math.random() * length);
      let res = ' ';
      for(let i = 0; i < length; ++i) {
        if(randInt === i) { res = arr[i]; return res; }
      }
    }
    this.showState = () => undefined;
    this.totalDisplays = () => [];    
    //createState(s: string,transitions: Transition[]): this
    this.createState = (s,transitions) => {
      let createdS = new State(s); //create new state object
      let helper = (t) => {
        let collision = Object.keys(t)[0];
        let c = getPropertyValue(t,collision); //get the values of the states at that event
        let total = this.totalDisplays();
        let end = total.find(x => x.getName() === c); 
        if(end === undefined) {
          end = new State(c);
          total.push(end);
          this.totalDisplays = () => total;
        }
        createdS.addTransition(collision, end);
      }  
      transitions.forEach(helper);
      let all = this.totalDisplays();
      let allThan = all.filter(inp => inp.getName() !== createdS.getName());
      allThan.push(createdS);
      this.totalDisplays = () => allThan;
      if(this.showState() === undefined) {
        this.showState = () => createdS.getName();
      }
      return this;
    }
    
    //createMemento(): Memento
    this.createMemento = () => { 
      let x = new Memento(this.showState()); 
      return x; 
    }
    //restoreMemento(m: Memento): this
    this.restoreMemento = (m) => {
      let total = this.totalDisplays(); 
      let z = total.find(x => x.getName() === m.getState());
      if(z === undefined) {return this;}
      else {this.showState = () => z.getName(); return this;}
    }
    //addTransition(s: string, t: Transition): this
    this.addTransition = (s,t) => {
      let total = this.totalDisplays();
      let end = total.find(x => x.getName() === s);
      if(end === undefined) {
        end = new State(s);
        total.push(end);
      }
      let collision = object.keys(t)[0];
      let varN = getPropertyValue(t,collision);
      let c = total.find(x => x.getName() === varN);
      if(c === undefined) {
        c = new State(s);
        total.push(c);
      }
      end.addTransition(collision, c);
      return this;
    }
   //nextState(e: string): this
    this.nextState = (e) => {
      let state = this.showState();
      if(state !== undefined) {
        let total = this.totalDisplays();
        let maint = total.find(x => x.getName() === state);
        let possible = maint.nextState(e);
        if(possible === undefined) {this.showState = () => undefined;}
        else {this.showState = () => possible.getName();}
        }  
      return this;
    }
    //renameState(name: string,newName: string): this
    this.renameState = (name, newName) => {
      let total = this.totalDisplays();
      let prev = total.find(c => c.getName() === name);
      if(prev !== undefined) {
        prev.setName(newName);
      }
      return this;
    }
  }
}

//tests

//creating two test objects, one to test the moving between states, the other tests memento
let myMachine = new FSA()
.createState("delicates, low", [{mode: "normal, low"}, {temp: "delicates, medium"}])
.createState("normal, low", [{mode: "delicates, low"}, {temp: "normal, medium"}])
.createState("delicates, medium", [{mode: "normal, medium"}, {temp: "delicates, low"}])
.createState("normal, medium", [{mode: "delicates, medium"}, {temp: "normal, high"}])
.createState("normal, high", [{mode: "delicates, medium"}, {temp: "normal, low"}]);

let myMachine2 = new FSA()
.createState("delicates, low", [{mode: "normal, low"}, {temp: "delicates, medium"}])
.createState("normal, low", [{mode: "delicates, low"}, {temp: "normal, medium"}])
.createState("delicates, medium", [{mode: "normal, medium"}, {temp: "delicates, low"}])
.createState("normal, medium", [{mode: "delicates, medium"}, {temp: "normal, high"}])
.createState("normal, high", [{mode: "delicates, medium"}, {temp: "normal, low"}]);

/*
myMachine.nextState("temp") // moves the machine to delicates, medium
.nextState("mode") // moves the machine to normal, medium
.nextState("temp"); // moves the machine to normal, high
let restoreTo = myMachine.createMemento(); // creates memento from current state
console.log(restoreTo.getState()); // prints name of state in memento
myMachine.nextState("mode") // moves the machine to delicates, medium
.nextState("temp") // moves the machine to delicates, low
.restoreMemento(restoreTo); // restores the machine to normal, high

*/

//console.log(myMachine.nextState("temp").display());

//testing the movement between states
test("checking one next state", function() {
  assert(myMachine.nextState("temp").showState() === 'delicates, medium');
});
test("checking two next state", function() {
  assert(myMachine.nextState("mode").showState() === 'normal, medium');
});
test("checking three next state", function() {
  assert(myMachine.nextState("temp").showState() === 'normal, high');
});
test("checking four next state", function() {
  assert(myMachine.nextState("mode").showState() === 'delicates, medium');
});
//testing memento 
test("checking memento", function() {
  myMachine2.nextState("temp") // moves the machine to delicates, medium
  .nextState("mode") // moves the machine to normal, medium
  .nextState("temp"); // moves the machine to normal, high
  let restoreTo = myMachine2.createMemento(); // creates memento from current state
  myMachine2.nextState("mode") // moves the machine to delicates, medium
  .nextState("temp"); // moves the machine to delicates, low
  assert(myMachine2.restoreMemento(restoreTo).showState() === 'normal, high');
});

//checking how memenoto works and fixing mine
/*

  myMachine.nextState("temp") // moves the machine to delicates, medium
  .nextState("mode") // moves the machine to normal, medium
  .nextState("temp"); // moves the machine to normal, high
  console.log(myMachine.display());
  let restoreTo = myMachine.createMemento(); // creates memento from current state
  myMachine.nextState("mode") // moves the machine to delicates, medium
  .nextState("temp"); // moves the machine to delicates, low
  console.log(myMachine.display());
  myMachine.restoreMemento(restoreTo);
  console.log(myMachine.display());
  console.log(myMachine.restoreMemento(restoreTo).display());

  */
        

        