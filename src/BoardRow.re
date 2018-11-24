let component = ReasonReact.statelessComponent("BoardRow");
let str = ReasonReact.string;

open SharedTypes;

let make = (~row, _children) => {
  ...component,
  render: _self =>
    <div className="row">
      {
        row
        |> Js.Array.map((square: square) =>
             <Square key=square##_id square />
           )
        |> ReasonReact.array
      }
    </div>,
};