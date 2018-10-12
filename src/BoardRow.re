let component = ReasonReact.statelessComponent("BoardRow");
let str = ReasonReact.string;

open SharedTypes;

let make = (~row, ~click, _children) => {
  ...component,
  render: _self =>
    <div className="row">
      {
        row
        |> List.map((square: square) => {
             Js.log(square);
             <Square key={string_of_int(square.id)} square click />;
           })
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};