## Reasonable-photos

This project is a frontend for [ownphotos](https://github.com/hooram/ownphotos). Although there is a [frontend](https://github.com/hooram/ownphotos-frontend) project already available, I felt it is time to upgrade its tech stack.

#### Tech stack
 - Reasonml
 - Reactjs
 - Reason-React
 - Expo
 - Material UI

#### Testing
  I have tried to do a reasonable test coverage for this project. Following test libraries are used

  - Cypress for end-to-end testing
  - Jest-expo library for unit testing

#### How to build
Start the project using below commands

```bash
    git clone https://github.com/Yokeshthirumoorthi/Reasonable-photos.git
    cd Reasonable-photos
    yarn
    yarn build && yarn web
```

#### Testing

Run Cypress e2e test

```bash
yarn cypress:open
```

Jest:
You could write jest tests using both reason and js.
As convention, the js test files end as *.test.js and reasonml test files ends as *_test.re

To run jest tests

```bash
yarn test
```

#### Authors

- Yokesh Thirumoorthi (Yokeshthirumoorthi@gmail.com)

#### License
This program is licensed under the "MIT License". Please see the file LICENSE in the source distribution of this software for license terms.