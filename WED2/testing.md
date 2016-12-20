# Testing

> * Argumente für automatisiertes Testen (Karten)
> * Unit Test Patternz zur Vorgehensweise zum Schreiben von Tests (Karten)
> * Test-Doubles/Mock-Objects 
> * Test-Driven / Test-First Design
> * Test-Smells erkennen und Refactorings durchführen
> * Kennen von BDD Konzepten und mit Jasmine Spezifikation einsetzen
> * TDD (TEst Driven Design) im Projekt einsetzen


## Double vs. Fake fs. Stub vs. Mock

| Pattern      | Purpose                         | Has Behaviour | Injects indirect inputs into SUT | Handles indirect outputs of SUT           | Values provided by test      |
|--------------|---------------------------------|---------------|----------------------------------|-------------------------------------------|------------------------------|
| Test Double  | Generic name for family         |               |                                  |                                           |                              |
| Dummy Object | Attribute/Method Parameter      | no            | no, never called                 | no, never called                          | no                           |
| Test Stub    | Verify indirect inputs of SUT   | yes           | yes                              | ignores them                              | inputs                       |
| Test Spy     | Verify indirect outputs of SUT  | yes           | optional                         | captures them for later verification      | inputs (optional)            |
| Mock Object  | Verify indirect outputs of SUT  | yes           | optional                         | verifies correctness against expectations | output and inputs (optional) |
| Fake Object  | Run (unrunnable) tests (faster) | yes           | no                               | uses them                                 | none                         |

=> Entkopelung relevant!


## Testing mit Jasmine

Jasmine basiert auf der "Sprache" von BDD (Behaviour-Driven Development). BDD ist eine erweiterung ovn Test-Driven Development (TDD).

```js
var BankAccount = require(process.env.bankaccount || "./bank-account");


// new bank account test suite
describe("A new bank account", function() {
	beforeEach(function() {
		this.account = new BankAccount();
	});

	it("is initialized by a balance of 0", function() {
		expect(this.account.balance).toBe(0);
	});

	it("should not allow a withdraw without balance", function() {
		expect(this.account.withdraw(50)).toBeFalsy();
		expect(this.account.balance).toBe(0);
	});

	it("should have a balance of 50 after a deposit of 50", function() {
		expect(this.account.deposit(50)).toBeTruthy();
		expect(this.account.balance).toBe(50);
	});
});

// 50$ bank account test suite
describe("A bank account of balance 50", function() {
	beforeEach(function() {
		this.account = new BankAccount();
		this.account.balance = 50;
	});

	it("should not allow to withdraw 13 (26%)", function() {
		expect(this.account.withdraw(13)).toBeFalsy();
		expect(this.account.balance).toBe(50);
	});

	it("should allow to withdraw 12.5 (25%)", function() {
		expect(this.account.withdraw(12.5)).toBeTruthy();
		expect(this.account.balance).toBe(37.5);
	});
});
```
