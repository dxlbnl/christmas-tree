<script lang="ts">
  import Select from '$lib/Select.svelte'
  import { config } from '$lib/config'
  import type { PageData } from './$types';

  export let data: PageData;

  const programChange = ({ target }: Event) => config({ program: (target as HTMLSelectElement).value })
  const brightnessChange = ({ target }: Event) => config({ brightness: (target as HTMLInputElement).valueAsNumber })
</script>

<!-- svelte-ignore a11y-label-has-associated-control -->
<label>
  Program:
  <Select
    options={data.programs}
    bind:value={data.config.program}
    on:change={e => programChange(e)}
  />
</label>

<label>
  Brightness:
  <input bind:value={data.config.brightness} type='range' min=1 max=255 on:change={brightnessChange} />
</label>

<style>
  label {
    display: block;
  }
</style>
