let component = ReasonReact.statelessComponent("Square");
let str = ReasonReact.string;

open SharedTypes;

let make = (~square, ~click, _children) => {
  ...component,
  render: _self =>
    square.isTaken ?
      <h1 className="square"> {str("X")} </h1> :
      <div
        className="square"
        key={string_of_int(square.id)}
        onClick={_evt => click(square)}>
        <h1> {str("X " ++ string_of_int(square.x))} </h1>
        <h1> {str("Y " ++ string_of_int(square.y))} </h1>
      </div>,
};