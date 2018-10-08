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

type row = list(square);

type board = list(row);

let makeRow = i => Belt.List.makeBy(10, j => {isTaken: false, id: i + j, x: i, y: j});

let board: board = [
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
];

let make = _children => {
  ...component,
  render: _self =>
    <div className="App">
      <h1> {str("Squares")} </h1>
      {
        board
        |> List.map(row =>{
            <h1>{str("Test")}</h1>
          }
        )
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};