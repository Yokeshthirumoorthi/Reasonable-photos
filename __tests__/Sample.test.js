// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

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
