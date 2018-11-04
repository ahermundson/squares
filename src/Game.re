type game = {_id: string};

let component = ReasonReact.statelessComponent("Game");

let make = (~selectGame, ~game, _children) => {
  ...component,
  render: _self =>
    <h1 onClick={_evt => selectGame()}> {ReasonReact.string(game##_id)} </h1>,
};