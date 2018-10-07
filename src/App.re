[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let str = ReasonReact.string;

type square = {
  id: int,
  isTaken: bool,
  x: int,
  y: int
};

type row = array(square);

type board = array(row);

let makeRow = i => Belt.Array.makeBy(10, j => {isTaken: false, id: i + j, x: i, y: j});

let board: board = [|
  makeRow(0),
  makeRow(1),
  makeRow(2),
  makeRow(3),
  makeRow(4),
  makeRow(5),
  makeRow(6),
  makeRow(7),
  makeRow(8),
  makeRow(9)
|];

let make = _children => {
  ...component,
  render: _self =>
    <div className="App">
      <h1> {str("Squares")} </h1>
      {
        board
        |> Array.map(row =>
             row
             |> Array.map(square => 
                <div key={string_of_int(square.id)}>
                  <h1>{str("X " ++ string_of_int(square.x))}</h1>
                  <h1>{str("Y " ++ string_of_int(square.y))}</h1>
                  <BoardRow />
                </div>
                )
              |> ReasonReact.array
           )
        |> ReasonReact.array
      }
    </div>,
};