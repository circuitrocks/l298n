# L298N — dual H-bridge motor driver

Sample sketch for the **[L298N Dual H-Bridge Motor Driver](https://circuit.rocks/products/2a-dual-motor-controller)**, sold by [Circuitrocks](https://circuit.rocks/).

This example drives two DC motors forward, backward, and at varying speeds using only built-in Arduino functions — **no external library required**.

## What you need

- 1x L298N module
- 1x Arduino Uno (or compatible)
- 1x or 2x DC motors (3–35 V, up to 2 A continuous per channel)
- 1x external power supply for the motors (battery pack, AC adapter, etc.)
- Jumper wires

## Wiring

| L298N pin | Arduino Uno pin | Purpose                  |
|-----------|-----------------|--------------------------|
| IN1       | D5              | Motor A direction        |
| IN2       | D6              | Motor A direction        |
| ENA       | D9 (PWM)        | Motor A speed            |
| IN3       | D7              | Motor B direction        |
| IN4       | D8              | Motor B direction        |
| ENB       | D10 (PWM)       | Motor B speed            |
| GND       | GND             | Shared ground (required) |

**Motor power:**

- `+12V` → external supply, **4.5–35 V** (matched to your motor's voltage rating).
- `+5V` → can power the Arduino itself if the on-board 5 V regulator jumper is in place AND the motor supply is **≤ 12 V**.
- For motor supplies **> 12 V**, REMOVE the on-board 5 V regulator jumper to avoid frying the regulator, and power the Arduino separately.

The Arduino and L298N **must share GND**. Don't skip this — it's the most common reason "the motors don't move".

## How to use

1. Open `l298n.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno** and the correct COM port.
3. Click **Upload** *before* connecting the motor power supply.
4. Connect the motor supply.
5. Open **Tools → Serial Monitor**, baud rate **9600** — you'll see status messages.
6. The motors cycle: forward → stop → reverse → stop → spin-in-place → stop, repeating.

## How it works

- `IN1`/`IN2` (and `IN3`/`IN4`) set the direction of each motor: `HIGH/LOW` = forward, `LOW/HIGH` = reverse, `LOW/LOW` or `HIGH/HIGH` = stop/brake.
- `ENA`/`ENB` are PWM pins. Writing 0 stops the motor; writing 255 runs it at full speed; values in between scale the speed roughly linearly.
- The `motorA(int speed)` helper takes `-255..+255` to combine direction and speed in one call. Same for `motorB()`.

## Notes

- The L298N drops about **2 V** across each H-bridge transistor pair. A 12 V supply only delivers ~10 V to the motor under load. For higher efficiency, consider a MOSFET-based driver like the DRV8833 or TB6612FNG.
- PWM frequency on Arduino Uno's pins D9/D10 is ~490 Hz — fine for most DC motors, but you may hear a faint whine.
- The chip gets hot under load. The on-board heatsink handles up to ~1 A continuous comfortably. Above that, add airflow or an external heatsink.

## Datasheet

[L298N datasheet & pinout (docs.circuit.rocks)](https://docs.circuit.rocks/motors/l298n/)

## Troubleshooting

- **Motors don't move** — check GND is shared between Arduino and L298N. Then check the motor power supply is connected and switched on.
- **Only one motor works** — verify all 6 control pins are wired (it's easy to miss ENA or ENB).
- **Motors run weakly** — the supply voltage isn't reaching the motors due to the 2 V drop. Use a higher-voltage supply or a more efficient driver.
- **Unexpected reverse direction** — swap the two motor lead wires (or flip `IN1` and `IN2` in code).

## License

MIT — see [LICENSE](LICENSE).

## Got stuck?

Drop by [circuit.rocks](https://circuit.rocks/) — happy to help our customers get their modules working.
