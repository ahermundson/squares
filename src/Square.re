let component = ReasonReact.statelessComponent("Square");
let str = ReasonReact.string;

type square = {
  id: int,
  isTaken: bool,
  x: int,
  y: int,
};

let make = (~square, ~click, _children) => {
  ...component,
  render: _self =>
    <div
      className="square"
      key={string_of_int(square.id)}
      onClick={_evt => click(square)}>
      <h1> {str("X " ++ string_of_int(square.x))} </h1>
      <h1> {str("Y " ++ string_of_int(square.y))} </h1>
    </div>,
};