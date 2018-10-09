let component = ReasonReact.statelessComponent("BoardRow");
let str = ReasonReact.string;

type square = {
  id: int,
  isTaken: bool,
  x: int,
  y: int,
};

let make = (~row, _children) => {
  ...component,
  render: _self =>
    row
    |> List.map((square: Square.square) => <Square square />)
    |> Array.of_list
    |> ReasonReact.array,
};