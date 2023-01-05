<script lang='ts'>
  import Patterns from '$lib/control/Patterns.svelte'
  
  import Block from '$lib/component/Block.svelte'
  import ColorPicker from '$lib/component/Colorpicker.svelte'
</script>

<Block
  as='main'
  style="
    display: grid;
    grid-template:
      'pattern layers' auto / 1fr 3fr;
  "
>
  <Patterns />
  <Block>
    <h1>Layers</h1>

    <Block>
      <h2>Fill</h2>
  
      <ColorPicker />
    </Block>
  </Block>
</Block>

