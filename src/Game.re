let component = ReasonReact.statelessComponent("Game");

let make = (~game, _children) => {
  ...component,
  render: _self => <h1> {ReasonReact.string(game##_id)} </h1>,
};