[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type row = list(Square.square);
type board = list(row);

let makeRow = i =>
  Belt.List.makeBy(10, (j: int) =>
    ({isTaken: false, id: i + j, x: i, y: j}: Square.square)
  );

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
  makeRow(9),
];

type state = {board};

type action =
  | ClickSquare(Square.square);

let component = ReasonReact.reducerComponent("App");

let test = (square: Square.square): unit => Js.log(square);

let str = ReasonReact.string;

let make = _children => {
  ...component,
  initialState: () => ({board: board}: state),
  reducer: (action: action, state: state) =>
    switch (action) {
    | ClickSquare(square) => ReasonReact.Update({board: state.board})
    },
  render: _self =>
    <div className="App">
      <h1> {str("Squares")} </h1>
      {
        board
        |> List.map(row => <BoardRow row click=test />)
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};