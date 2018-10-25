type game = {_id: string};

let component = ReasonReact.statelessComponent("Game");

let make = (~selectGame, ~game, _children) => {
  ...component,
  render: self => {
    Js.log(self.state);
    <h1 onClick={_evt => selectGame()}> {ReasonReact.string(game##_id)} </h1>;
  },
};