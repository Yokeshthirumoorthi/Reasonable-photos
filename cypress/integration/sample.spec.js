import { Machine } from 'xstate';
import { createModel } from '@xstate/test';

const welcomeMachine = Machine({
    id: 'welcome',
    initial: 'welcome',
    states: {
        welcome: {
            on: {
                ShowIntroText: 'intro'
            },
            meta: {
                test: () => {
                    cy.get('[data-testid="toggle-button"]');
                    cy.contains('Welcome Message');
                }
            }
        },
        intro: {
            on: {
                ShowWelcomeText: 'welcome2'
            },
            meta: {
                test: () => {
                    cy.get('[data-testid="toggle-button"]');
                    cy.contains('Intro Message');
                }
            }
        },
        welcome2: {
            on: {
                ShowIntroText: 'intro'
            },
            meta: {
                test: () => {
                    cy.get('[data-testid="toggle-button"]');
                    cy.contains('Welcome Message');
                }
            }
        },
    }
});


const testWelcomeModel = createModel(welcomeMachine).withEvents({
    ShowIntroText: {
        exec: () =>
            cy.get('[data-testid="toggle-button"]')
                .click()
    },
    ShowWelcomeText: {
        exec: () =>
            cy.get('[data-testid="toggle-button"]')
                .click()
    }
});

describe("Welome Model", () => {
    // Create the test plans
    const testPlans = testWelcomeModel.getSimplePathPlans();

    testPlans.forEach((plan, planIndex) => {
        describe(`Plan ${planIndex}: ${plan.description}`, () => {

            // Start with an empty list for the failur patterns for this plan.
            plan.paths.forEach((path, pathIndex) => {
                it(`Path ${pathIndex}: ${path.description}`, () => {
                    cy.visit('/').then(() => {
                        return new Cypress.Promise(async (resolve) => {
                            await path.test(cy);
                            resolve();
                        });
                    });
                });
            });
        });
    });
});