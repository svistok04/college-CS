# Rules

There are a number of rules for writing safer applications:

- Do not discard values returned by functions. When exceptions are disabled 
  (like in many embedded development frameworks), errors are notified to 
  users with return values. If you discard them, it means that you ignore 
  errors. Use the `[[nodiscard]]` construction for forcing users not to 
  discard return values.
- Use `enums` as error types and prefer scoped enums to unscoped enums. 
  Scoped enums are written using the 
  As a