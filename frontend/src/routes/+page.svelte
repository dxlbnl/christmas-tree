<script lang="ts">
  import {HsvPicker} from 'svelte-color-picker';

  let color = 'red'
</script>

<h1>Lights</h1>


<input type='color' bind:value={color} />
<HsvPicker  bind:/>