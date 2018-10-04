[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

type square = {
  id: int,
  isTaken: bool
};

let squares: array(square) = [|
  {id: 1, isTaken: false},
  {id: 2, isTaken: false},
  {id: 3, isTaken: false}
|];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className="App">
      <h1>(ReasonReact.string("Squares"))</h1>
      {
        squares
        |> Array.map(square =>
             <h1 key=string_of_int(square.id)>(ReasonReact.string(string_of_int(square.id)))</h1>
           )
        |> ReasonReact.array
      }
    </div>,
};
