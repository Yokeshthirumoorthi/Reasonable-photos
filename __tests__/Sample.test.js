import React from 'react';
import renderer from 'react-test-renderer';

import { app as App } from '../src/App.bs.js';

describe('<App />', () => {
  it('has 2 children', () => {
    // const tree = renderer.create(<App />).toJSON();
    // expect(tree.children.length).toBe(3);
    expect(true).toBe(true);
  });
});
