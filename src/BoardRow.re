let component = ReasonReact.statelessComponent("BoardRow");

let make = _children => {
    ...component,
    render: _self => {
        <div><h1>{ReasonReact.string("Test")}</h1></div>
    }
}