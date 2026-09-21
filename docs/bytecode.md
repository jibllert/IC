## Items

| Type          |Short          | Value         |
| ------------- |:-------------:|:-------------:|
| Variable def  | VDEF          |0x00           |


## Var defs

IC `unsigned int num = 5;`
ICBC(hex)`00 00 02 00 05`
`00` = `bytecode_key.define`
`00` = `definitions.variable`
`02` = `definitions.variables.int`
`00` = `definitions.variables.flags`
`05` = `<value>`
