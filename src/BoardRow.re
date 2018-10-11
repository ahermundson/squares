let component = ReasonReact.statelessComponent("BoardRow");
let str = ReasonReact.string;

type square = {
  id: int,
  isTaken: bool,
  x: int,
  y: int,
};

let make = (~row, ~click, _children) => {
  ...component,
  render: _self =>
    <div className="row">
      {
        row
        |> List.map((square: Square.square) => {
             Js.log(square);
             <Square key={string_of_int(square.id)} square click />;
           })
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};